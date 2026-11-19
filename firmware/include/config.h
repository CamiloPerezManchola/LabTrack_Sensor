#pragma once

#include <Arduino.h>

// ==========================================
// Hardware
// ==========================================
constexpr uint8_t PIN_DHT   = 23;  // Pin de datos del DHT22
constexpr uint8_t PIN_RELAY = 2;   // LED integrado (solo si se activa NODRIX_WRITE)

// ==========================================
// Temporización y comunicación
// ==========================================
#ifndef TELEMETRY_INTERVAL_MS
constexpr unsigned long TELEMETRY_INTERVAL_MS = 12000; // 12 s (cuida la cuota gratuita)
#endif
// El DHT22 necesita al menos 2 s entre lecturas
static_assert(TELEMETRY_INTERVAL_MS >= 3000, "El DHT22 no admite lecturas mas rapidas que 2 s");

constexpr unsigned long SERIAL_BAUD_RATE = 115200;

// ==========================================
// Rangos válidos del DHT22
// ==========================================
constexpr float TEMP_MIN = -40.0f;
constexpr float TEMP_MAX = 80.0f;
constexpr float HUM_MIN  = 0.0f;
constexpr float HUM_MAX  = 100.0f;