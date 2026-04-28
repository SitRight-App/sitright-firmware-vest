#include "config.h"
#include "sensors.h"
#include "network.h"
#include "battery.h"

static unsigned long lastSendMs = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n[SITRIGHT] Iniciando chaleco SitRight...");

  initBattery();

  if (!initSensors()) {
    Serial.println("[SITRIGHT] Error critico en sensores. Reiniciando en 5s...");
    delay(5000);
    ESP.restart();
  }

  connectWiFi();
  Serial.println("[SITRIGHT] Listo. Enviando cada 5 segundos.");
}

void loop() {
  if (!isWiFiConnected()) {
    Serial.println("[SITRIGHT] WiFi perdido. Reconectando...");
    connectWiFi();
    return;
  }

  unsigned long now = millis();
  if (now - lastSendMs < SEND_INTERVAL_MS) {
    return;
  }
  lastSendMs = now;

  int battery = getBatteryPercent();
  Serial.printf("[SITRIGHT] Bateria: %d%%\n", battery);

  if (isBatteryLow()) {
    Serial.printf("[SITRIGHT] Bateria baja (%d%%). Enviando alerta final.\n", battery);
    VestReadings r = readSensors();
    sendReading(r, battery);
    Serial.println("[SITRIGHT] Entrando en deep sleep (30s).");
    esp_sleep_enable_timer_wakeup(30ULL * 1000000ULL);
    esp_deep_sleep_start();
    return;
  }

  VestReadings readings = readSensors();
  sendReading(readings, battery);
}
