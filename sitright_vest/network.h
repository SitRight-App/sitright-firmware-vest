#pragma once
#include "sensors.h"

bool connectWiFi();
bool isWiFiConnected();
bool sendReading(const VestReadings& readings, int batteryPercent);
