#include <Entropy.h>
#include <math.h>

#define SAMPLES 64          // Reduced number of samples
#define SAMPLING_FREQUENCY 500 // Reduced sampling frequency in Hz
#define OUT_FREQ SAMPLING_FREQUENCY / 2 // Maximum frequency we can analyze

void setup() {
  Serial.begin(115200);
  Entropy.Initialize();  // Initialize the watchdog timer for entropy
}

void loop() {
  int16_t samples[SAMPLES];
  int16_t real[SAMPLES];
  int16_t imag[SAMPLES];

  Serial.println("Random Numbers:");
  
  // Collect entropy-based random numbers as if they were analog data and print them
  for (int i = 0; i < SAMPLES; i++) {
    if (Entropy.available()) {
      uint32_t random_value = Entropy.random();
      samples[i] = map(random_value, 0, UINT32_MAX, -32768, 32767); // Map the random value to the int16_t range
      Serial.println(samples[i]); // Print the random value
    } else {
      samples[i] = 0; // If no entropy data is available, use zero
    }
    delayMicroseconds(1000000 / SAMPLING_FREQUENCY); // Delay to maintain the desired sampling frequency
  }

  Serial.println("FFT Calculations:");
  
  // Perform FFT manually
  FFT(samples, real, imag, SAMPLES);

  // Print the magnitude of the FFT results
  for (int i = 0; i < SAMPLES / 2; i++) {
    float magnitude = sqrt(real[i] * real[i] + imag[i] * imag[i]);
    float frequency = i * OUT_FREQ / (SAMPLES / 2);

    Serial.print(frequency, 2);
    Serial.print(" Hz: ");
    Serial.println(magnitude);
  }

  delay(1000); // Delay between FFT calculations
}

void FFT(int16_t* samples, int16_t* real, int16_t* imag, int sampleSize) {
  if (sampleSize <= 1) {
    // Base case: Nothing to do for a single sample or less
    real[0] = samples[0];
    imag[0] = 0;
  } else {
    // Recursive FFT implementation
    int N = sampleSize;

    // Split the input into even and odd samples
    int16_t evenReal[N / 2];
    int16_t evenImag[N / 2];
    int16_t oddReal[N / 2];
    int16_t oddImag[N / 2];

    for (int i = 0; i < N / 2; i++) {
      evenReal[i] = samples[2 * i];
      evenImag[i] = 0;
      oddReal[i] = samples[2 * i + 1];
      oddImag[i] = 0;
    }

    // Recursive FFT on even and odd halves
    FFT(evenReal, evenReal, evenImag, N / 2);
    FFT(oddReal, oddReal, oddImag, N / 2);

    // Combine results
    for (int k = 0; k < N / 2; k++) {
      float theta = -2 * PI * k / N; // Phase factor
      int16_t tReal = cos(theta) * oddReal[k] - sin(theta) * oddImag[k];
      int16_t tImag = cos(theta) * oddImag[k] + sin(theta) * oddReal[k];

      real[k] = evenReal[k] + tReal;
      imag[k] = evenImag[k] + tImag;
      real[k + N / 2] = evenReal[k] - tReal;
      imag[k + N / 2] = evenImag[k] - tImag;
    }
  }
}
