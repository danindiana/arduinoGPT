#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

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

  // Calibrate gyroscope
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  mpu.setThreshold(3);
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
