const int laserPin = 9;
const char* message = "Hello, Laser!";

// Configuration
const int baudRate = 2400;
const int interval = 1000000 / baudRate;
const int startBitCount = 3;

void setup() {
  pinMode(laserPin, OUTPUT);
}

void loop() {
  // Send start bits
  for (int i = 0; i < startBitCount; i++) {
    digitalWrite(laserPin, HIGH);
    delayMicroseconds(interval);
    digitalWrite(laserPin, LOW);
    delayMicroseconds(interval);
  }

  // Send message
  for (int i = 0; message[i] != '\0'; i++) {
    sendByte(message[i]);
  }

  // Wait 3 seconds before transmitting again
  delay(3000);
}

void sendByte(char byteToSend) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(laserPin, (byteToSend & (1 << i)) ? HIGH : LOW);
    delayMicroseconds(interval);
  }
  digitalWrite(laserPin, LOW);
  delayMicroseconds(interval);
}
