const int sensorPin = A0;
const int sensorThreshold = 500;

// Configuration
const int baudRate = 2400;
const int interval = 1000000 / baudRate;
const int startBitCount = 3;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  if (analogRead(sensorPin) > sensorThreshold) {
    // Wait for start bits
    bool startBitsDetected = true;
    for (int i = 0; i < startBitCount; i++) {
      delayMicroseconds(interval);
      if (analogRead(sensorPin) <= sensorThreshold) {
        startBitsDetected = false;
        break;
      }
      delayMicroseconds(interval);
    }

    if (startBitsDetected) {
      // Receive message
      while (true) {
        char receivedByte = receiveByte();
        if (receivedByte == '\0') break;
        Serial.print(receivedByte);
      }
      Serial.println();
    }
  }
}

char receiveByte() {
  char receivedByte = 0;

  for (int i = 0; i < 8; i++) {
    delayMicroseconds(interval);
    if (analogRead(sensorPin) > sensorThreshold) {
      receivedByte |= (1 << i);
    }
    delayMicroseconds(interval);
  }

  return receivedByte;
}
