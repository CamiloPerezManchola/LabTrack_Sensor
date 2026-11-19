#include "sensors.h"
#include "config.h"
#include <DHT.h>
#include <math.h>

static DHT dht(PIN_DHT, DHT22);

static SensorReading make_reading(float v, float lo, float hi) {
    SensorReading r{};
    r.value = v;
    r.valid = !isnan(v) && !isinf(v) && v >= lo && v <= hi;
    return r;
}

void sensors_init() {
    dht.begin();
}

SensorData sensors_read() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // Un único reintento si hubo fallo de lectura
    if (isnan(h) || isnan(t)) {
        delay(500);
        h = dht.readHumidity();
        t = dht.readTemperature();
    }

    SensorData data{};
    data.temperatura = make_reading(t, TEMP_MIN, TEMP_MAX);
    data.humedad     = make_reading(h, HUM_MIN, HUM_MAX);
    return data;
}