#pragma once

#include <Arduino.h>

struct SensorReading {
    float value;
    bool valid;
};

struct SensorData {
    SensorReading temperatura;
    SensorReading humedad;
};

/** Inicializa el sensor DHT22. */
void sensors_init();

/** Lee temperatura y humedad; marca como inválida cualquier lectura fallida. */
SensorData sensors_read();