#include <Wire.h>
#include <vector>

// MPU-6050 I2C address
#define MPU6050_ADDR 0x68

// Struct to hold sensor data and timestamp
struct SensorData {
  unsigned long timestamp;
  int16_t accelX, accelY, accelZ;
  int16_t gyroX, gyroY, gyroZ;
};

// Vector to hold the last 10 seconds of sensor data
std::vector<SensorData> sensorData;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  delay(100);
}

void loop() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 14, true); // request a total of 14 registers

  SensorData data;
  data.timestamp = millis();
  data.accelX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  data.accelY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  data.accelZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  data.gyroX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  data.gyroY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  data.gyroZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  sensorData.push_back(data);

  // If we have more than 10 seconds of data, remove the oldest
  if (sensorData.size() > 100) {
    sensorData.erase(sensorData.begin());
  }

  delay(100);  // Adjust this delay to match the actual time it takes to read and process the data
}
