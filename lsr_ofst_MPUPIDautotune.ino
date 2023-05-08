#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Servo.h>
#include <Encoder.h>
#include <MPU6050_tockn.h>
#include <PID_v1.h>

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

// Servo objects
Servo servoX;
Servo servoY;

// BMP280 object
Adafruit_BMP280 bmp280;

// Encoders for X and Y axes
Encoder encoderX(encoderXPins[0], encoderXPins[1]);
Encoder encoderY(encoderYPins[0], encoderYPins[1]);

// MPU6050 object
MPU6050 mpu6050(Wire);

// PID Controllers
double inputX, inputY, outputX, outputY;
double setpointX = 0, setpointY = 0;
double kP = 1, kI = 1, kD = 1;

PID pidX(&inputX, &outputX, &setpointX, kP, kI, kD, DIRECT);
PID pidY(&inputY, &outputY, &setpointY, kP, kI, kD, DIRECT);

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

  // Initialize MPU6050
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // Initialize PID controllers
  pidX.SetMode(AUTOMATIC);
  pidY.SetMode(AUTOMATIC);
}

void loop() {
  opticalSensorValue = digitalRead(opticalSensorPin);
  float currentHeight = getCurrentHeight();

  // Update MPU6050 data
  mpu6050.update();

  // Automatically adjust PID gains based on MPU6050 gyro data
  updatePIDGains();

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
  servoXPosition = (
