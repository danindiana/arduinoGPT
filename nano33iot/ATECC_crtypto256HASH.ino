#include <SparkFun_ATECCX08a_Arduino_Library.h>
#include <Wire.h>

ATECCX08A atecc;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!atecc.begin()) {
    Serial.println("Failed to initialize ATECC chip!");
    while (1);
  }
}

void loop() {
  // Get a random number to incorporate into the message
  long random_number = random(0, 10000);  // Generate a random number between 0 and 9999

  // Create a message string with the random number
  String message = "Message with random number: " + String(random_number);

  // Ensure message is null-terminated
  message.reserve(message.length() + 1);
  message += '\0';

  // Create a non-const uint8_t array for compatibility
  uint8_t message_data[message.length() + 1];
  memcpy(message_data, message.c_str(), message.length() + 1);

  // Get SHA-256 hash
  uint8_t sha256_hash[32];
  atecc.sha256(message_data, message.length(), sha256_hash);

  // Print the hash and original message to the serial monitor
  Serial.println("Original message: " + message);
  Serial.print("SHA-256 Hash: ");
  for (int i = 0; i < 32; i++) {
    char buffer[4];
    sprintf(buffer, "%02X", sha256_hash[i]);
    Serial.print(buffer);
  }
  Serial.println();
  Serial.println();  // Add an extra line for readability

  delay(140);
}
