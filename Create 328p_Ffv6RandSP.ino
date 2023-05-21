#include "arduinoFFT.h"
#include "Entropy.h"  // Include the Entropy library

#define SAMPLES 64 // Must be a power of 2
#define SAMPLING_FREQUENCY 1000 // Max for Arduino Uno is around 9kHz due to hardware limitations

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

arduinoFFT FFT = arduinoFFT();

enum WINDOW_TYPE {
  HAMMING,
  HANNING,
  BLACKMAN,
  FLATTOP
};

WINDOW_TYPE windowType;

void setup() {
  Serial.begin(9600);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));

  // Initialize the entropy library
  Entropy.initialize();
}

double generateRandom() {
  double randomValue = 0;
  for(int i = 0; i < 3; i++) {
    randomValue += Entropy.random(SAMPLES);
  }
  return randomValue/3; // Average to get number between 0 and SAMPLES-1
}

void loop() {
  for (int i = 0; i < 4; i++) {
    windowType = static_cast<WINDOW_TYPE>(i);

    /* Generating Test Data */
    microseconds = micros();
    for(int i=0; i<SAMPLES; i++) {
      // Generate a random value between 0 and SAMPLES-1
      vReal[i] = generateRandom();
      Serial.println(vReal[i]); // Plot the input data
      vImag[i] = 0;
      while(micros() - microseconds < sampling_period_us){
        // wait to sample at correct time interval
      }
      microseconds += sampling_period_us;
    }

    Serial.println("-1"); // Input data marker
    delay(100); // Short delay for visibility

    /* Performing FFT */
    unsigned long start_time = micros();
    switch (windowType) {
      case HAMMING:
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        break;
      case HANNING:
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); // Use Hamming for Hanning
        break;
      case BLACKMAN:
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_BLACKMAN, FFT_FORWARD);
        break;
      case FLATTOP:
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_FLT_TOP, FFT_FORWARD); // Use FFT_WIN_TYP_FLT_TOP for Flattop
        break;
    }
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    unsigned long end_time = micros();

    Serial.println("-1"); // Output data marker
    delay(100); // Short delay for visibility

    for (int i = 0; i < SAMPLES; i++) {
      Serial.println(vReal[i]); // Plot the output data
    }

    Serial.print("Execution Time for ");
    switch (windowType) {
      case HAMMING:
        Serial.print("HAMMING: ");
        break;
      case HANNING:
        Serial.print("HANNING: ");
        break;
      case BLACKMAN:
        Serial.print("BLACKMAN: ");
        break;
      case FLATTOP:
        Serial.print("FLATTOP: ");
        break;
    }
    Serial.print(end_time - start_time);
    Serial.println(" microseconds");
  }
  delay(1000); // Perform test once per second
}
