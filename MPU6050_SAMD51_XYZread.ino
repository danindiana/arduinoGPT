#include <Wire.h>
#include <MPU6050.h>
#include <ArduinoFFT.h>

#define SAMPLES 64 // SAMPLES-pt FFT. Adjust as needed
#define SAMPLING_FREQUENCY 1000 // Max expected frequency in Hz

double vRealX[SAMPLES];
double vImagX[SAMPLES];

double vRealY[SAMPLES];
double vImagY[SAMPLES];

double vRealZ[SAMPLES];
double vImagZ[SAMPLES];

unsigned int sampling_period_us;
unsigned long microseconds;

MPU6050 mpu;

void setup() 
{
  Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }

  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

void loop()
{
  /* Sampling */
  for(int i=0; i<SAMPLES; i++)
  {
    microseconds = micros();    // Overflows after around 70 minutes!
   
    Vector rawAccel = mpu.readRawAccel(); // Reading acceleration data

    vRealX[i] = rawAccel.XAxis;
    vImagX[i] = 0;

    vRealY[i] = rawAccel.YAxis;
    vImagY[i] = 0;

    vRealZ[i] = rawAccel.ZAxis;
    vImagZ[i] = 0;

    // Wait until sampling period us has passed since we took the last sample data
    while(micros() < microseconds + sampling_period_us){
      // do nothing to wait out the sample period
    }
  }

  /* FFT for X axis */
  FFT.Windowing(vRealX, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vRealX, vImagX, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vRealX, vImagX, SAMPLES);
  double peakX = FFT.MajorPeak(vRealX, SAMPLES, SAMPLING_FREQUENCY);

  /* FFT for Y axis */
  FFT.Windowing(vRealY, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vRealY, vImagY, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vRealY, vImagY, SAMPLES);
  double peakY = FFT.MajorPeak(vRealY, SAMPLES, SAMPLING_FREQUENCY);

  /* FFT for Z axis */
  FFT.Windowing(vRealZ, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vRealZ, vImagZ, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vRealZ, vImagZ, SAMPLES);
  double peakZ = FFT.MajorPeak(vRealZ, SAMPLES, SAMPLING_FREQUENCY);

  /* Print out frequency of audio peak for each axis */
  Serial.print("PeakX: ");
  Serial.println(peakX);
  
  Serial.print("PeakY: ");
  Serial.println(peakY);
  
  Serial.print("PeakZ: ");
  Serial.println(peakZ);

  delay(1000);
}
