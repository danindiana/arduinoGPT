#include <Arduino_LSM6DS3.h> // Correct library for LSM6DS3 on Arduino Nano 33 IoT and UNO WiFi Rev 2
#include <SparkFun_ATECCX08a_Arduino_Library.h>
#include <Wire.h>

ATECCX08A atecc; // Create an instance of the ATECCX08A object

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for the serial port to connect

  Wire.begin();

  // Initialize ATECC chip
  if (!atecc.begin()) {
    Serial.println("Failed to initialize ATECC chip!");
    while (1); // Infinite loop to halt further execution
  }

  // Initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1); // Infinite loop to halt further execution
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;

  // Check if acceleration data is available
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Display acceleration data
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);

    // Combine random number with scaled and shifted acceleration data for entropy
    long random_number = random(0, 10000);
    long entropy = map(x * 1000, -4000, 4000, -500, 500) + map(y * 1000, -4000, 4000, -500, 500) + map(z * 1000, -4000, 4000, -500, 500);
    random_number ^= entropy; // Bitwise XOR for mixing

    // Create message string with random number
    String message = "Message with random number: " + String(random_number);

    // Create a non-const uint8_t array for compatibility
    uint8_t message_data[message.length() + 1];
    memcpy(message_data, message.c_str(), message.length() + 1);

    // Get SHA-256 hash
    uint8_t sha256_hash[32];
    atecc.sha256(message_data, message.length(), sha256_hash);

    // Print the hash and original message to the serial monitor
    Serial.print("Original message: ");
    Serial.println(message);
    Serial.print("SHA-256 Hash: ");
    for (int i = 0; i < 32; i++) {
      Serial.print(sha256_hash[i], HEX);
    }
    Serial.println("\n"); // Add an extra line for readability
  }

  delay(1000); // Slow down the loop to make it easier to read the output
}
