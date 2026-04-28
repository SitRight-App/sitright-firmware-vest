#pragma once

// ─── WiFi ──────────────────────────────────────────────────────────────────
#define WIFI_SSID     "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// ─── Backend ───────────────────────────────────────────────────────────────
// Para Wokwi/local: usar HTTP → http://localhost:8000/api/v1/readings
// Para producción:  usar HTTPS → https://sitright-backend-api.onrender.com/api/v1/readings
#define BACKEND_URL      "http://localhost:8000/api/v1/readings"
#define BACKEND_USE_HTTPS 0   // 0 = HTTP (Wokwi/local) | 1 = HTTPS (Render)

#define VEST_ID "vest-wokwi-001"

// ─── Timing ────────────────────────────────────────────────────────────────
#define SEND_INTERVAL_MS 5000

// ─── I2C Bus 1 — cervical (0x68) + dorsal (0x69, AD0=HIGH) ────────────────
#define I2C1_SDA 21
#define I2C1_SCL 22

// ─── I2C Bus 2 — lumbar (0x68, AD0=LOW) ───────────────────────────────────
#define I2C2_SDA 16
#define I2C2_SCL 17

// ─── Batería ───────────────────────────────────────────────────────────────
#define BATTERY_PIN           34
#define BATTERY_LOW_THRESHOLD 10
