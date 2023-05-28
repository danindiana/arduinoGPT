#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

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
  Vector rawAccel = mpu.readRawAccel();
  float magnitude = sqrt(rawAccel.XAxis*rawAccel.XAxis + rawAccel.YAxis*rawAccel.YAxis + rawAccel.ZAxis*rawAccel.ZAxis);

  // Use magnitude to set bandwidth
  if (magnitude < 500) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  } 
  else if (magnitude < 1000) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);
  } 
  else if (magnitude < 1500) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  } 
  else if (magnitude < 2000) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);
  } 
  else if (magnitude < 2500) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);
  } 
  else if (magnitude < 3000) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_184_HZ);
  } 
  else 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  }

  // The rest of your code goes here...
}
