#include "network.h"
#include "config.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

bool connectWiFi() {
  Serial.printf("[WIFI] Conectando a %s", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  for (int i = 0; i < 20 && WiFi.status() != WL_CONNECTED; i++) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("[WIFI] Conectado. IP: %s\n", WiFi.localIP().toString().c_str());
    return true;
  }
  Serial.println("[WIFI] No se pudo conectar.");
  return false;
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

bool sendReading(const VestReadings& r, int batteryPercent) {
  JsonDocument doc;
  doc["vest_id"] = VEST_ID;

  JsonArray cervical = doc["cervical"].to<JsonArray>();
  cervical.add(r.cervical.ax);
  cervical.add(r.cervical.ay);
  cervical.add(r.cervical.az);

  JsonArray dorsal = doc["dorsal"].to<JsonArray>();
  dorsal.add(r.dorsal.ax);
  dorsal.add(r.dorsal.ay);
  dorsal.add(r.dorsal.az);

  JsonArray lumbar = doc["lumbar"].to<JsonArray>();
  lumbar.add(r.lumbar.ax);
  lumbar.add(r.lumbar.ay);
  lumbar.add(r.lumbar.az);

  doc["battery_percent"] = batteryPercent;

  String payload;
  serializeJson(doc, payload);
  Serial.printf("[NET] Enviando: %s\n", payload.c_str());

  HTTPClient http;

#if BACKEND_USE_HTTPS
  WiFiClientSecure secureClient;
  secureClient.setInsecure();
  http.begin(secureClient, BACKEND_URL);
#else
  WiFiClient client;
  http.begin(client, BACKEND_URL);
#endif

  http.addHeader("Content-Type", "application/json");

  int code = http.POST(payload);
  if (code > 0) {
    Serial.printf("[NET] Respuesta %d: %s\n", code, http.getString().c_str());
    http.end();
    return code == 201;
  }
  Serial.printf("[NET] Error: %s\n", http.errorToString(code).c_str());
  http.end();
  return false;
}
