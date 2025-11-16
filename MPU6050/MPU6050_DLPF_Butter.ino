#include <Wire.h>
#include <MPU6050.h>
#include <Filter.h>

MPU6050 mpu;

// Create Butterworth filter
FilterOnePole butterworthFilter(LOWPASS_BUTTERWORTH, 5.0); // 5 Hz cutoff frequency

void setup() 
{
  Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }

  // Set initial bandwidth
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
}

void loop()
{
  Vector rawAccel = mpu.readRawAccel();
  float magnitude = sqrt(rawAccel.XAxis*rawAccel.XAxis + rawAccel.YAxis*rawAccel.YAxis + rawAccel.ZAxis*rawAccel.ZAxis);

  // Apply Butterworth filter to magnitude
  float filteredMagnitude = butterworthFilter.input(magnitude);

  // Use filtered magnitude to set bandwidth
  // Modify these threshold values as per your requirements
  if (filteredMagnitude < 500) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  } 
  else if (filteredMagnitude < 1000) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);
  } 
  else if (filteredMagnitude < 1500) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  } 
  else if (filteredMagnitude < 2000) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);
  } 
  else if (filteredMagnitude < 2500) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);
  } 
  else if (filteredMagnitude < 3000) 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_184_HZ);
  } 
  else 
  {
    mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  }

  // The rest of your code goes here...
}
