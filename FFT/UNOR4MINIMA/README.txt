Tested on Arduino IDE for Linux Ubuntu

Version: 2.3.0
Date: 2024-02-07T13:40:55.118Z
CLI Version: 0.35.2

Copyright © 2024 Arduino SA

Uses arduinoFFT.h
https://github.com/kosme/arduinoFFT


This Arduino code snippet demonstrates the use of the arduinoFFT library to perform a Fast Fourier Transform (FFT) on a synthetically generated signal. The FFT is a powerful tool in signal processing, allowing for the analysis of the frequency components within a signal. Here's a step-by-step explanation:

1. Setup and Initialization
Include Libraries: The code includes the arduinoFFT library for FFT operations, <math.h> for mathematical functions, and <random> for generating random numbers.
Define Constants and Variables:
Constants like samples, signalFrequency, samplingFrequency, and amplitude are defined for signal generation and FFT analysis.
Arrays vReal and vImag store real and imaginary parts of the signal, respectively.
signalBuffer and windowSize are used for smoothing the signal.
A random number generator is initialized for adding noise to the signal.
2. setup()
Initializes the serial connection for output.
Prints an introductory message.
3. loop()
This is where the main functionality resides, executed in a loop.

Signal Generation
Simulated Sine Wave Generation: A loop generates a sine wave with a frequency of signalFrequency, adding a random perturbation to simulate noise or chaotic behavior.
Smoothing: Before storing the signal in vReal, it passes through a simple smoothing filter using signalBuffer to average over windowSize samples.
Windowing
Hamming Window: Applies a Hamming window to the signal using FFT.Windowing to reduce spectral leakage.
FFT Computation
FFT Execution: Performs FFT on the windowed signal to convert it from the time domain to the frequency domain. The real and imaginary parts of the signal are stored in vReal and vImag.
Magnitude Calculation
Complex to Magnitude: Converts the complex FFT output into magnitude to analyze the signal's strength across different frequencies.
Peak Detection
Identify Dominant Frequency: Finds and prints the frequency with the highest magnitude, indicative of the most prominent signal component.
Helper Functions
printData(): A utility function for printing the data with labels, used to output the FFT results and magnitudes.
Execution Flow
The loop() function starts by generating a sine wave with added noise and smoothing.
It then applies a Hamming window to minimize side lobes in the FFT output.
The FFT is computed on the windowed signal.
The magnitudes of the frequency components are calculated.
The dominant frequency in the signal is identified and printed.
Additional Notes
The signal is periodically perturbed with random noise (perturbation) to simulate a real-world, non-ideal signal.
Smoothing is applied to mitigate the effects of the perturbation and to simulate a moving average filter.
The delay() functions are used to space out serial outputs for readability.
This process repeats indefinitely, with each loop iteration generating, processing, and analyzing a new signal instance.
