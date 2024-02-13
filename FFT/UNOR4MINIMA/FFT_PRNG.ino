#include "arduinoFFT.h" 
#include <math.h>
#include <random>

arduinoFFT FFT; 

// Constants - Modify these for experimentation
const uint16_t samples = 64; 
const double signalFrequency = 30;  // Start with a lower value
const double samplingFrequency = 2000; 
const uint8_t amplitude = 100;          

// Smoothing parameters
const int windowSize = 5; // Adjust as needed

double vReal[samples];
double vImag[samples];
double signalBuffer[windowSize] = {0}; // Initialize the buffer with zeros
int bufferIndex = 0;

// Declare random generator globally
std::default_random_engine generator(1561415); 

// Helper to print data with labels
void printData(double *data, uint16_t length, const char* xAxisLabel) {  
  for (int i = 0; i < length; i++) {
    Serial.print(i * 1000.0 / samplingFrequency, 2); 
    Serial.print(" ");
    Serial.print(xAxisLabel);
    Serial.print("  "); 
    Serial.println(data[i]);
    delay(100); // Delay of 100 ms
  }
  Serial.println(); 
}

void setup() {
  Serial.begin(9600);
  Serial.println("FFT Functionality Demonstration");
}

void loop() {
  // 1. Signal Generation (with chaotic modifications)
  Serial.println("--- Simulated Sine Wave (Chaotic) ---");
  for (int i = 0; i < samples; i++) {
    double ratio = 2.0 * PI * signalFrequency / samplingFrequency;
    double phaseOffset = sqrt(2.0) * i * ratio; 

    // Random perturbation using PRNG 
    std::uniform_real_distribution<double> dist(-0.05, 0.05); 
    double perturbation = dist(generator); 

    // Apply smoothing
    signalBuffer[bufferIndex] = (amplitude + perturbation) * sin(i * ratio + phaseOffset);
    bufferIndex = (bufferIndex + 1) % windowSize;

    double smoothedValue = 0;
    for (int j = 0; j < windowSize; j++) {
        smoothedValue += signalBuffer[j];
    }
    smoothedValue /= windowSize;

    vReal[i] = smoothedValue; // Use the smoothed value
    vImag[i] = 0; 

    Serial.print(vReal[i]); // DEBUG: Print generated value
    Serial.print(" "); 
  }
  Serial.println(); 

  // 2. Windowing (Hamming)
  Serial.println("--- Hamming Window Applied ---");
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); 

  // 3. FFT Computation
  Serial.println("--- FFT Computed ---");
  FFT = arduinoFFT(vReal, vImag, samples, samplingFrequency); 
  FFT.Compute(FFT_FORWARD); 
  printData(vReal, samples, "Sample Index"); // Print FFT output (real)
  printData(vImag, samples, "Sample Index"); // Print FFT output (imaginary)

  // 4. Magnitude Calculation
  Serial.println("--- Magnitudes ---");
  FFT.ComplexToMagnitude();
  printData(vReal, samples / 2, "Frequency (Hz)"); 

  // 5. Peak Detection
  Serial.println("--- Peak Frequency ---");
  double peakFrequency = FFT.MajorPeak();
  Serial.print("Dominant Frequency: ");
  Serial.print(peakFrequency, 2);
  Serial.println(" Hz");

  delay(300); // Pause for output viewing 
}
