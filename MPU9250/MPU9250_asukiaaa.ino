#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("started");

#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  // You can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;
}

void loop() {
  uint8_t sensorId;
  int result;

  result = mySensor.readId(&sensorId);
  if (result == 0) {
    Serial.println("sensorId: " + String(sensorId));
  } else {
    Serial.println("Cannot read sensorId " + String(result));
  }

  // Get all sensor readings at once
  if (mySensor.accelUpdate() != 0) { 
    Serial.println("Failed to read accelerometer");
    return; // Exit loop early if there's an error
  }  
  aX = mySensor.accelX();
  aY = mySensor.accelY();
  aZ = mySensor.accelZ();
  aSqrt = mySensor.accelSqrt();

  if (mySensor.gyroUpdate() != 0) {
    Serial.println("Failed to read gyroscope");
    return;
  }
  gX = mySensor.gyroX();
  gY = mySensor.gyroY();
  gZ = mySensor.gyroZ();

  // Handle potential magUpdate errors as before
  result = mySensor.magUpdate();
  if (result != 0) {
    Serial.println("Cannot read mag values " + String(result));
    mySensor.beginMag();
    result = mySensor.magUpdate();
  }
  if (result == 0) {
    mX = mySensor.magX();
    mY = mySensor.magY();
    mZ = mySensor.magZ();
    mDirection = mySensor.magHorizDirection();
  }

  // Output data to Serial Plotter
  Serial.print(aX); Serial.print(" ");
  Serial.print(aY); Serial.print(" ");
  Serial.print(aZ); Serial.print(" ");
  Serial.print(aSqrt); Serial.print(" ");
  Serial.print(gX); Serial.print(" ");
  Serial.print(gY); Serial.print(" ");
  Serial.print(gZ); Serial.print(" ");
  Serial.print(mX); Serial.print(" ");
  Serial.print(mY); Serial.print(" ");
  Serial.print(mZ); Serial.print(" ");
  //Serial.println(mDirection); 

  //Serial.println("at " + String(millis()) + "ms");
  //Serial.println(""); // Add an empty line
  delay(100);
}
