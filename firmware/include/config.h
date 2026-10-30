
#pragma once

#include <Arduino.h>

// ==========================================
// Configuración de Hardware y Sensores
// ==========================================

// Pines ADC1 (GPIO 32-39)
// ADC1 permite utilizar Wi-Fi simultáneamente.
// Resolución ADC: 12 bits (0-4095).

constexpr uint8_t PIN_TEMP  = 34; // Potenciómetro: Temperatura
constexpr uint8_t PIN_HUM   = 35; // Potenciómetro: Humedad
constexpr uint8_t PIN_LUX   = 32; // Potenciómetro: Iluminancia
constexpr uint8_t PIN_NOISE = 33; // Potenciómetro: Ruido simulado

// Sensor PIR: entrada digital
constexpr uint8_t PIN_PIR = 27;

// ==========================================
// Configuración ADC
// ==========================================

constexpr uint8_t  ADC_RESOLUTION = 12;
constexpr uint16_t ADC_MAX_VAL    = 4095;

// Atenuación del ADC para ampliar el rango medible.
constexpr uint8_t ADC_ATTENUATION_DB = 11;

// ==========================================
// Temporización y Comunicación
// ==========================================

constexpr unsigned long TELEMETRY_INTERVAL_MS = 1000;
constexpr unsigned long SERIAL_BAUD_RATE      = 115200;

constexpr uint16_t HTTP_TIMEOUT_MS = 15000;
constexpr uint32_t TLS_HANDSHAKE_TIMEOUT_S = 30;

// ==========================================
// Rangos Físicos de Escalado
// ==========================================

// Temperatura: 0 - 60 °C
constexpr float TEMP_MIN = 0.0f;
constexpr float TEMP_MAX = 60.0f;

// Humedad relativa: 0 - 100 %
constexpr float HUM_MIN = 0.0f;
constexpr float HUM_MAX = 100.0f;

// Iluminancia: 0 - 1000 lux
constexpr float LUX_MIN = 0.0f;
constexpr float LUX_MAX = 1000.0f;

// Ruido: 0 - 100 % (valor relativo simulado)
// No representa directamente decibelios (dB).
constexpr float NOISE_MIN = 0.0f;
constexpr float NOISE_MAX = 100.0f;

// ==========================================
// Configuración del Sensor PIR
// ==========================================

constexpr uint8_t PIR_DETECTED    = HIGH;
constexpr uint8_t PIR_NOT_DETECTED = LOW;

// ==========================================
// Identificación del Proyecto
// ==========================================

constexpr char DEVICE_NAME[] = "LabTrack";
constexpr char DEVICE_VERSION[] = "0.1.0";
constexpr char DEVICE_MODE[] = "WOKWI_SIMULATION";
