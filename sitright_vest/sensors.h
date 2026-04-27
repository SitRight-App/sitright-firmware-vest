#pragma once

struct SensorReading {
  float ax, ay, az;
};

struct VestReadings {
  SensorReading cervical;
  SensorReading dorsal;
  SensorReading lumbar;
};

bool    initSensors();
VestReadings readSensors();
