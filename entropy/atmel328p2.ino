#include <Entropy.h>

const double samplingFrequency = 250; // Wave generation rate

void setup() {
  Serial.begin(115200);  
  Entropy.Initialize();     
}

void loop() {
  // Angle for sine wave calculation
  static double angle = 0.0;      
  double angleIncrement = 2.0 * PI / samplingFrequency; 

  // Randomness from Entropy
  double randomFrequencyFactor = Entropy.random(100, 11800) / 1000.0;  // Scale for variation
  double randomAmplitudeFactor = Entropy.random(10, 4000) / 10.0;      // Scale for variation

  // Adjust wave parameters with randomness
  double frequency = 5.0 + (randomFrequencyFactor * 10.0);   // Example: 5 - 15 Hz  
  double amplitude = 50.0 * randomAmplitudeFactor;      

  // Generate a fluctuating sine wave
  double y = amplitude * sin(angle * frequency); //  Varying freq AND amplitude 

  // Serial Plotter Output
  Serial.println(y); 

  // Update angle for next sample
  angle += angleIncrement; 

  // Control generation speed
  //delay(50 / samplingFrequency);  
}
