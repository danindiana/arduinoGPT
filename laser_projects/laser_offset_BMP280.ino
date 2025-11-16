#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Servo.h>

// Constants
const int opticalSensorPin = 2;
const int servoXPin = 9;
const int servoYPin = 10;
const int threshold = 100;

// Variables
int opticalSensorValue;
int servoXPosition = 90;
int servoYPosition = 90;

// Servo objects
Servo servoX;
Servo servoY;

// BMP280 object
Adafruit_BMP280 bmp280;

void setup() {
  Serial.begin(9600);
  
  if (!bmp280.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  pinMode(opticalSensorPin, INPUT);

  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  servoX.write(servoXPosition);
  servoY.write(servoYPosition);
}

void loop() {
  opticalSensorValue = digitalRead(opticalSensorPin);
  float currentHeight = getCurrentHeight();

  // If the canister is aligned with the laser, adjust the control system
  if (opticalSensorValue == HIGH) {
    alignWithLaser();
  }

  // If the canister has traversed the predetermined point in the descending trajectory
  if (currentHeight < threshold) {
    moveToOffsetIndicator();
  }

  delay(50);
}

void alignWithLaser() {
  // Implement control logic here to align the canister with the laser
  
  // As an example, we adjust the servo positions by a small increment
  servoXPosition = (servoXPosition + 1) % 180;
  servoYPosition = (servoYPosition + 1) % 180;

  servoX.write(servoXPosition);
  servoY.write(servoYPosition);
}

float getCurrentHeight() {
  float altitude = bmp280.readAltitude();
  return altitude;
}

void moveToOffsetIndicator() {
  // Implement logic to guide the can
