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
      int16_t tReal = cos(2 * PI * k / N) * oddReal[k] - sin(2 * PI * k / N) * oddImag[k];
      int16_t tImag = cos(2 * PI * k / N) * oddImag[k] + sin(2 * PI * k / N) * oddReal[k];

      real[k] = evenReal[k] + tReal;
      imag[k] = evenImag[k] + tImag;
      real[k + N / 2] = evenReal[k] - tReal;
      imag[k + N / 2] = evenImag[k] - tImag;
    }
  }
}
