#include <SPI.h>
#include <vector>

// MPU-9250 SPI configurations
#define MPU9250_CS_PIN 10
#define SPI_SPEED 1000000 // 1MHz

// Struct to hold sensor data and timestamp
struct SensorData {
  unsigned long timestamp;
  int16_t accelX, accelY, accelZ;
  int16_t gyroX, gyroY, gyroZ;
  int16_t magX, magY, magZ;
};

// Vector to hold the last 10 seconds of sensor data
std::vector<SensorData> sensorData;

void setup() {
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16); // Set SPI clock speed
  pinMode(MPU9250_CS_PIN, OUTPUT);
  digitalWrite(MPU9250_CS_PIN, HIGH);
  delay(100);
}

void loop() {
  SensorData data;
  data.timestamp = millis();

  // Read accelerometer data
  data.accelX = readRegister(0x3B) << 8 | readRegister(0x3C);
  data.accelY = readRegister(0x3D) << 8 | readRegister(0x3E);
  data.accelZ = readRegister(0x3F) << 8 | readRegister(0x40);

  // Read gyroscope data
  data.gyroX = readRegister(0x43) << 8 | readRegister(0x44);
  data.gyroY = readRegister(0x45) << 8 | readRegister(0x46);
  data.gyroZ = readRegister(0x47) << 8 | readRegister(0x48);

  // Read magnetometer data
  data.magX = readRegister(0x49) << 8 | readRegister(0x4A);
  data.magY = readRegister(0x4B) << 8 | readRegister(0x4C);
  data.magZ = readRegister(0x4D) << 8 | readRegister(0x4E);

  sensorData.push_back(data);

  // If we have more than 10 seconds of data, remove the oldest
  if (sensorData.size() > 100) {
    sensorData.erase(sensorData.begin());
  }

  delay(100);  // Adjust this delay to match the actual time it takes to read and process the data
}

byte readRegister(byte thisRegister) {
  byte inByte = 0 ;
  digitalWrite(MPU9250_CS_PIN, LOW);
  SPI.transfer(thisRegister | 0x80); // Set the most significant bit to indicate a read operation
  inByte = SPI.transfer(0x00); // Read the data
  digitalWrite(MPU9250_CS_PIN, HIGH);
  return inByte;
}
