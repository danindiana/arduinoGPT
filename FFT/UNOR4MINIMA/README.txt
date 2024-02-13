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

Here's how you can slow down the wave's speed in the Arduino Serial Plotter, along with factors to consider:

1. Reduce Data Transmission Rate

Baud Rate: In your Arduino code, lower the baud rate in the Serial.begin() function. (e.g., Serial.begin(9600); for slower transmission). Slower baud rates mean fewer data points transmitted per second, making the wave appear to move slower on the plotter.
2. Introduce Delays

Within the loop: Add a delay() function within your Arduino's loop() function. This creates pauses between sending data points, which will spread them out over time on the Serial Plotter.
3. Control Data Sampling Rate

Change how often you take readings: If you're plotting sensor data, don't take readings as frequently. Increase the interval between sensor readings or introduce a counter before collecting the next data point.
Important Considerations:

Trade-off: Slowing down the wave speed also means you'll see fewer data points in a given timeframe. This might make it harder to see intricate details of your signal.
Desired effect: How much you want to slow down the wave depends on what you're trying to observe. Experiment with different adjustments to find a good balance.
Example:

Arduino
void setup() {
  Serial.begin(9600);  // Slower baud rate
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(200);  // Delay of 200 milliseconds 
}
Use code with caution.
Let me know if you'd like a more specific code example tailored to your project!

profile picture
what does this mean:  "const double samplingFrequency = 5000"?
Here's a breakdown of the code "const double samplingFrequency = 5000":

const: This keyword declares that the value of samplingFrequency cannot be changed once it's assigned. It acts as a constant throughout your code.
double: This specifies the data type. 'Double' means the variable is designed to store high-precision floating-point numbers (numbers with decimals).
samplingFrequency: This is the chosen name for the variable. The name descriptively implies that it will hold information about the rate at which samples are taken.
= 5000: This assigns the value 5000 to the variable samplingFrequency.
In essence, this line of code means:

You are creating a constant value named samplingFrequency that will store a high-precision number.  This number, 5000,  represents the rate at which something is being sampled.

Possible Implications (depends on the context of your code):

Audio Processing: It's very likely this indicates 5000 samples are taken per second from an audio signal. This is a common sampling frequency for capturing sound.
Sensor readings: It could mean 5000 readings are collected per second from a sensor (temperature, light, etc.).
Let me know if you can share the surrounding code; I can give you a much more specific interpretation of its function!
