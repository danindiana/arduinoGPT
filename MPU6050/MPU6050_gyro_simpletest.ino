#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Function to perform communication test
bool communicationTest() {
  // Assuming 0x75 is the register holding a known value (0x68)
  uint8_t registerValue = mpu.readByte(0x75);
  return (registerValue == 0x68);  // 0x68 is expected value for MPU6050
}

// Function to perform self-test
bool selfTest() {
  // Run built-in self test
  return mpu.selfTest();
}

void setup() 
{
  Serial.begin(115200);

  // Initialize MPU6050
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Perform communication test
  if (!communicationTest())
  {
    Serial.println("Communication with MPU6050 failed, check wiring!");
    while(1);  // Infinite loop if communication test fails
  }
  
  // Perform self test
  if (!selfTest())
  {
    Serial.println("MPU6050 self-test failed, check sensor!");
    while(1);  // Infinite loop if self test fails
  }
  
  // Calibration and threshold setting...
  
  // Check settings
  checkSettings();
}

void loop()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();

  // Printing only once every second, adjust as needed
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 1000)
  {
    lastPrint = millis();

    Serial.print(" Xraw = ");
    Serial.print(rawGyro.XAxis);
    Serial.print(" Yraw = ");
    Serial.print(rawGyro.YAxis);
    Serial.print(" Zraw = ");
    Serial.println(rawGyro.ZAxis);

    Serial.print(" Xnorm = ");
    Serial.print(normGyro.XAxis);
    Serial.print(" Ynorm = ");
    Serial.print(normGyro.YAxis);
    Serial.print(" Znorm = ");
    Serial.println(normGyro.ZAxis);
  }
}
