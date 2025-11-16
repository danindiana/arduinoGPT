#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Servo.h>
#include <Encoder.h>

// Constants
const int opticalSensorPin = 2;
const int servoXPin = 9;
const int servoYPin = 10;
const int threshold = 100;

// Encoder pins for X and Y axes
const int encoderXPins[] = {3, 4};
const int encoderYPins[] = {5, 6};

// Variables
int opticalSensorValue;
int servoXPosition = 90;
int servoYPosition = 90;

// Target position and control gain
float targetX = 0;
float targetY = 0;
float kP = 0.1;

// Servo objects
Servo servoX;
Servo servoY;

// BMP280 object
Adafruit_BMP280 bmp280;

// Encoders for X and Y axes
Encoder encoderX(encoderXPins[0], encoderXPins[1]);
Encoder encoderY(encoderYPins[0], encoderYPins[1]);

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
 
