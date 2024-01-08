#include <Entropy.h>

void setup() {
  Serial.begin(115200);
  Entropy.Initialize();  // Initialize the watchdog timer for entropy
}

void loop() {
  if (Entropy.available()) {  // Check if new entropy is available
    uint32_t random_value = Entropy.random();  // Get the random value directly from the watchdog timer
    Serial.println(random_value);  // Print the random value to the serial monitor
  }
}
