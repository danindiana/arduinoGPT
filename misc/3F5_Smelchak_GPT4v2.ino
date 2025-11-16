#include <Servo.h>

// Pin connections
const int panServoPin = 9;
const int tiltServoPin = 10;
const int sensorPin = A0;

// Servo motor instances
Servo panServo;
Servo tiltServo;

// Configuration
const int sensorThreshold = 700;
const int servoStep = 5;

void setup() {
  Serial.begin(9600);
  panServo.attach(panServoPin);
  tiltServo.attach(tiltServoPin);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // If the sensor value is below the threshold, move the servos to seek the laser
  if (sensorValue < sensorThreshold) {
    int panAngle = panServo.read();
    int tiltAngle = tiltServo.read();

    // Move pan servo
    if (panAngle + servoStep <= 180) {
      panServo.write(panAngle + servoStep);
    } else {
      panServo.write(panAngle - servoStep);
    }

    // Move tilt servo
    if (tiltAngle + servoStep <= 180) {
      tiltServo.write(tiltAngle + servoStep);
    } else {
      tiltServo.write(tiltAngle - servoStep);
    }
  }

  delay(100);
}
