#include <Adafruit_MPU6050.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200); // Adjust baud rate if needed
  while (!Serial) {
    delay(10);
  }

  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }
}

void loop() {
  sensors_event_t a, g, temp; // Declare all event structures (necessary)

  mpu.getEvent(&a, &g, &temp); // Read all sensor data

  // Access only accelerometer and gyroscope data selectively
  Serial.print(a.acceleration.x);
  Serial.print(", "); // Added comma and space separator
  Serial.print(a.acceleration.y);
  Serial.print(", "); // Added comma and space separator
  Serial.println(a.acceleration.z);

  delay(250); // Increased delay to 250 milliseconds
}
