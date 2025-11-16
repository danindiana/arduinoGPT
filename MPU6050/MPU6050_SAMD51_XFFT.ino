#include <Wire.h>
#include <MPU6050.h>
#include <ArduinoFFT.h> 

#define SAMPLES 64 //SAMPLES-pt FFT. Adjust as needed
#define SAMPLING_FREQUENCY 1000 //Max expected frequency in Hz

double vReal[SAMPLES];
double vImag[SAMPLES];

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
    microseconds = micros();    //Overflows after around 70 minutes!
   
    Vector rawAccel = mpu.readRawAccel(); // Reading acceleration data

    vReal[i] = rawAccel.XAxis;
    vImag[i] = 0;

    //Wait until sampling period us has passed since we took the last sample data
    while(micros() < microseconds + sampling_period_us){
      // do nothing to wait out the sample period
    }
  }

  /* FFT */
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

  /* Print out frequency of audio peak */
  Serial.println(peak);
  
  delay(1000);
}
