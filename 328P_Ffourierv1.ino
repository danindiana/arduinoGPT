#include "arduinoFFT.h"

#define SAMPLES 64 // Must be a power of 2
#define SAMPLING_FREQUENCY 1000 // Max for Arduino Uno is around 9kHz due to hardware limitations

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

arduinoFFT FFT = arduinoFFT();

void setup() {
  Serial.begin(9600);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop() {
  /* Generating Test Data */
  microseconds = micros();
  for(int i=0; i<SAMPLES; i++) {
    vReal[i] = i;
    vImag[i] = 0;
    while(micros() - microseconds < sampling_period_us){
      // wait to sample at correct time interval
    }
    microseconds += sampling_period_us;
  }
  /* Performing FFT */
  unsigned long start_time = micros();
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  unsigned long end_time = micros();

  Serial.print("Execution Time: ");
  Serial.print(end_time - start_time);
  Serial.println(" microseconds");

  delay(1000); // Perform test once per second
}
