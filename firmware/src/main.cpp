#include <Arduino.h>
#include "config.h"
#include "sensors.h"
#include "telemetry.h"

static unsigned long last_telemetry_time = 0;

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    while (!Serial && millis() < 2000) {
        ;
    }

    Serial.println();
    Serial.println(F("=================================================="));
    Serial.println(F("  Monitoreo de laboratorio - ESP32 + DHT22        "));
    Serial.println(F("=================================================="));

    sensors_init();
    Serial.printf("[Hardware] DHT22 configurado en GPIO%u.\n", PIN_DHT);

    telemetry_init();

    Serial.printf("[Sistema] Publicacion programada cada %lu segundos.\n\n",
                  TELEMETRY_INTERVAL_MS / 1000);
}

void loop() {
    // Mantener Nodrix.run() de forma continua, sin bloqueos
    telemetry_run();

    unsigned long current_time = millis();

    if (current_time - last_telemetry_time >= TELEMETRY_INTERVAL_MS) {
        last_telemetry_time = current_time;

        SensorData data = sensors_read();

        Serial.printf("T=%lu ms | Temp: %.1f C%s | Hum: %.1f %%%s\n",
                      current_time,
                      data.temperatura.value,
                      data.temperatura.valid ? "" : " [INVALID]",
                      data.humedad.value,
                      data.humedad.valid ? "" : " [INVALID]");

        telemetry_publish(data);
    }
}