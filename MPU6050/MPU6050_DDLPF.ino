#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int potPin = A0; // Analog pin connected to the potentiometer

void setup() 
{
  Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }

  // Set initial bandwidth
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
}

void loop()
{
  int potValue = analogRead(potPin); // Read potentiometer value

  // Use potentiometer value to set bandwidth
  if (potValue < 100) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  } 
  else if (potValue < 200) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);
  } 
  else if (potValue < 300) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  } 
  else if (potValue < 400) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);
  } 
  else if (potValue < 500) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);
  } 
  else if (potValue < 600) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_184_HZ);
  } 
  else 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  }

  // The rest of your code goes here...
}
