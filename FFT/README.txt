For arduino_entropy_FFT.ino

This code performs two main tasks:

1. Collecting Entropy-Based Random Numbers:

The Entropy.h library utilizes hardware resources to gather randomness from environmental noise or other unpredictable sources.
SAMPLES number of 16-bit integer samples are collected.
Each sample is obtained by calling Entropy.random() if enough entropy is available, otherwise it's set to 0.
The random values are mapped to the int16_t range (-32768 to 32767) and printed to the serial monitor.
The collection time is measured and printed.
2. Fast Fourier Transform (FFT) Calculation:

The collected samples are treated as an analog signal and analyzed for frequency content.
A manual implementation of the Fast Fourier Transform (FFT) algorithm is used to compute the magnitude of each frequency component.
Only the first third of the frequencies are analyzed as the Nyquist limit restricts meaningful results past half the sampling frequency.
The frequency and magnitude for each analyzed component are printed to the serial monitor.
The FFT calculation time is measured and printed.
Key Points:

The code relies on the Entropy.h library for randomness generation.
It demonstrates a basic approach to using entropy as a source of randomness.
The manual FFT implementation showcases the algorithm but might not be the most efficient choice in all scenarios.
The printed values provide insights into the frequency distribution of the random numbers obtained from the entropy source.
Additional Notes:

The specific behavior of the Entropy.h library might vary depending on the hardware and implementation details.
Alternative libraries or approaches can be used for both random number generation and FFT calculations.
Consider optimizing the FFT implementation for better performance if necessary.
