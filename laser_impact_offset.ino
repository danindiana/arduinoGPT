#include <Servo.h>

// Constants
const int opticalSensorPin = 2;  // Optical sensor input pin
const int servoXPin = 9;         // Servo X axis control pin
const int servoYPin = 10;        // Servo Y axis control pin

const int threshold = 100;       // Threshold to determine if the canister has traversed the predetermined point

// Variables
int opticalSensorValue;
int currentHeight;
int servoXPosition = 90;
int servoYPosition = 90;

// Servo objects
Servo servoX;
Servo servoY;

void setup() {
  pinMode(opticalSensorPin, INPUT);

  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  servoX.write(servoXPosition);
  servoY.write(servoYPosition);

  Serial.begin(9600);
}

void loop() {
  opticalSensorValue = digitalRead(opticalSensorPin);
  currentHeight = getCurrentHeight();  // Replace this with a function to get the current height or altitude

  // If the canister is aligned with the laser, adjust the control system
  if (opticalSensorValue == HIGH) {
    alignWithLaser();
  }

  // If the canister has traversed the predetermined point in the descending trajectory
  if (currentHeight < threshold) {
    moveToOffsetIndicator();  // Replace this with a function to guide the canister to the desired offset indicator
  }

  delay(50);
}

void alignWithLaser() {
  // Implement control logic here to align the canister with the laser
  // Adjust the servos or actuation system to guide the canister towards the laser
  
  // As an example, we adjust the servo positions by a small increment
  servoXPosition = (servoXPosition + 1) % 180;
  servoYPosition = (servoYPosition + 1) % 180;

  servoX.write(servoXPosition);
  servoY.write(servoYPosition);
}
