#include "sensors.h"
#include "config.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

static Adafruit_MPU6050 mpuCervical;
static Adafruit_MPU6050 mpuDorsal;
static Adafruit_MPU6050 mpuLumbar;

static const float G = 9.81f;

bool initSensors() {
  Wire.begin(I2C1_SDA, I2C1_SCL);
  Wire1.begin(I2C2_SDA, I2C2_SCL);

  if (!mpuCervical.begin(0x68, &Wire)) {
    Serial.println("[SENSORS] Error: MPU cervical (0x68, Wire)");
    return false;
  }
  if (!mpuDorsal.begin(0x69, &Wire)) {
    Serial.println("[SENSORS] Error: MPU dorsal (0x69, Wire — AD0=HIGH)");
    return false;
  }
  if (!mpuLumbar.begin(0x68, &Wire1)) {
    Serial.println("[SENSORS] Error: MPU lumbar (0x68, Wire1)");
    return false;
  }

  mpuCervical.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpuDorsal.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpuLumbar.setAccelerometerRange(MPU6050_RANGE_2_G);

  Serial.println("[SENSORS] OK: 3x MPU6050 inicializados");
  return true;
}

static SensorReading readOne(Adafruit_MPU6050& mpu) {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);
  SensorReading r;
  r.ax = accel.acceleration.x / G;
  r.ay = accel.acceleration.y / G;
  r.az = accel.acceleration.z / G;
  return r;
}

VestReadings readSensors() {
  VestReadings r;
  r.cervical = readOne(mpuCervical);
  r.dorsal   = readOne(mpuDorsal);
  r.lumbar   = readOne(mpuLumbar);
  return r;
}
