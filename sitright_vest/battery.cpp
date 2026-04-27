#include "battery.h"
#include "config.h"
#include <Arduino.h>

void initBattery() {
  pinMode(BATTERY_PIN, INPUT);
}

int getBatteryPercent() {
  // Divisor resistivo 100k+100k: LiPo 4.2V→2.1V, 3.0V→1.5V en ADC
  int raw = analogRead(BATTERY_PIN);
  float voltage = (raw / 4095.0f) * 3.3f * 2.0f;
  int percent = (int)((voltage - 3.0f) / (4.2f - 3.0f) * 100.0f);
  return constrain(percent, 0, 100);
}

bool isBatteryLow() {
  return getBatteryPercent() < BATTERY_LOW_THRESHOLD;
}
