#include <Wire.h>
#include <Adafruit_GPS.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Servo.h>
#include <MPU6050_tockn.h>
#include <PID_v1.h>

// Constants
const int opticalSensorPin = 2;
const int servoXPin = 9;
const int servoYPin = 10;

// Variables
int opticalSensorValue;
int servoXPosition = 90;
int servoYPosition = 90;

// Target position
float targetX = 0;
float targetY = 0;

// Servo objects
Servo servoX;
Servo servoY;

// BME280 object
Adafruit_BME280 bme;

// MPU6050 object
MPU6050 mpu6050(Wire);

// GPS object
Adafruit_GPS GPS(&Serial1);

// PID Controllers
double inputX, inputY, outputX, outputY;
double setpointX = 0, setpointY = 0;
double kP = 1, kI = 1, kD = 1;

PID pidX(&inputX, &outputX, &setpointX, kP, kI, kD, DIRECT);
PID pidY(&inputY, &outputY, &setpointY, kP, kI, kD, DIRECT);

void setup() {
  Serial.begin(115200);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
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

  // Initialize GPS
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);

  // Initialize PID controllers
  pidX.SetMode(AUTOMATIC);
  pidY.SetMode(AUTOMATIC);
}

void loop() {
  // Update GPS data
  GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      return;
    }
  }

  opticalSensorValue = digitalRead(opticalSensorPin);
  float currentAltitude = bme.readAltitude();

  // Update MPU6050 data
  mpu6050.update();

  // Guide the canister to the laser if detected
  if (opticalSensorValue == HIGH) {
    guideCanisterToTarget(currentAltitude);
  }
}

void guideCanisterToTarget(float currentAltitude) {
  // Get the current position of the canister
  inputX = getCurrentX();
  inputY = getCurrentY();

  // Set the target position of the canister
  setpointX = targetX;
  setpointY = targetY;

  // Compute the PID controller output
  pidX.SetTunings(Kp, Ki, Kd);
  pidY.SetTunings(Kp, Ki, Kd);
  pidX.Compute();
  pidY.Compute();

  // Calculate speed and trajectory adjustments based on altitude
  float altitudeFactor = calculateAltitudeFactor(currentAltitude);
  outputX *= altitudeFactor;
  outputY *= altitudeFactor;

  // Update servo positions based on the PID output
  servoXPosition = constrain(servoXPosition + outputX, 0, 180);
  servoYPosition = constrain(servoYPosition + outputY, 0, 180);

  // Write the updated servo positions
  servoX.write(servoXPosition);
  servoY.write(servoYPosition);
}

float calculateAltitudeFactor(float currentAltitude) {
  // Implement a function to calculate a factor based on the altitude
  // This factor should be used to adjust the control output based on the canister's altitude
  // The specific function can be derived through simulations, real-world testing, or a combination of both
  // For example, return a linear or non-linear function of currentAltitude

  // A simple example:
  return 1.0 - (currentAltitude / maxAltitude);
}

