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
const int searchRange = 180;

void setup() {
  Serial.begin(9600);
  panServo.attach(panServoPin);
  tiltServo.attach(tiltServoPin);
  panServo.write(searchRange / 2);
  tiltServo.write(searchRange / 2);
}

void loop() {
  int maxSensorValue = 0;
  int maxPanAngle = 0;
  int maxTiltAngle = 0;

  // Sweep the pan and tilt servos to search for the target
  for (int panAngle = 0; panAngle <= searchRange; panAngle += servoStep) {
    panServo.write(panAngle);

    for (int tiltAngle = 0; tiltAngle <= searchRange; tiltAngle += servoStep) {
      tiltServo.write(tiltAngle);
      delay(50); // Allow time for servos to move and sensor to stabilize

      int sensorValue = analogRead(sensorPin);

      if (sensorValue > maxSensorValue) {
        maxSensorValue = sensorValue;
        maxPanAngle = panAngle;
        maxTiltAngle = tiltAngle;
      }
    }
  }

  Serial.print("Max Sensor Value: ");
  Serial.print(maxSensorValue);
  Serial.print(" at Pan Angle: ");
  Serial.print(maxPanAngle);
  Serial.print(" and Tilt Angle: ");
  Serial.println(maxTiltAngle);

  // Move the servos to the position with the highest sensor value
  if (maxSensorValue > sensorThreshold) {
    panServo.write(maxPanAngle);
    tiltServo.write(maxTiltAngle);
  }

  delay(1000); // Wait for 1 second before the next search cycle
}
