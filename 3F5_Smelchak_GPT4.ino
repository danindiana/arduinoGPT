#include <Servo.h>
#include <Wire.h>

// Pin connections
const int servoPin = 9;
const int rangefinderAddress = 0x62; // I2C address of the laser rangefinder

// Servo motor instance
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  
  // Initialize rangefinder
  Wire.begin();
  configureRangefinder();
}

void loop() {
  int distance = readRangefinderDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  // Control servo motor based on the measured distance
  int servoAngle = map(distance, 0, 5000, 0, 180);
  servo.write(servoAngle);
  delay(500);
}

void configureRangefinder() {
  Wire.beginTransmission(rangefinderAddress);
  Wire.write(0x02); // Select the register to configure
  Wire.write(0x0a); // Set the measurement mode to High-Speed mode
  Wire.endTransmission();
}

int readRangefinderDistance() {
  int distance = 0;
  
  // Request distance measurement
  Wire.beginTransmission(rangefinderAddress);
  Wire.write(0x01); // Select the register to read
  Wire.endTransmission();

  // Read the distance measurement
  Wire.requestFrom(rangefinderAddress, 2);
  if (Wire.available() >= 2) {
    distance = Wire.read() << 8; // MSB
    distance |= Wire.read();      // LSB
  }

  return distance;
}
