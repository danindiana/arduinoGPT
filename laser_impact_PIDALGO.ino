#include <MPU6050_tockn.h>
#include <PID_v1.h>

MPU6050 mpu6050(Wire);

// PID Controllers
double inputX, inputY, outputX, outputY;
double setpointX = 0, setpointY = 0;
double kP = 1, kI = 1, kD = 1;

PID pidX(&inputX, &outputX, &setpointX, kP, kI, kD, DIRECT);
PID pidY(&inputY, &outputY, &setpointY, kP, kI, kD, DIRECT);

void setup() {
  Serial.begin(9600);

  // ... rest of your setup code
  
  // Initialize MPU6050
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // Initialize PID controllers
  pidX.SetMode(AUTOMATIC);
  pidY.SetMode(AUTOMATIC);
}
void moveToOffsetIndicator() {
  // Update MPU6050 data
  mpu6050.update();

  // Get the current position and orientation of the canister
  float currentX = getCurrentX();
  float currentY = getCurrentY();
  float currentAngleX = mpu6050.getAngleX();
  float currentAngleY = mpu6050.getAngleY();

  // Calculate the desired position based on the canister's orientation and speed
  setpointX = targetX + currentAngleX * mpu6050.getGyroX();
  setpointY = targetY + currentAngleY * mpu6050.getGyroY();

  // Update PID controller inputs
  inputX = currentX;
  inputY = currentY;

  // Compute the PID control outputs
  pidX.Compute();
  pidY.Compute();

  // Update the servo positions (make sure to limit the positions between 0 and 180 degrees)
  servoXPosition = constrain(servoXPosition + outputX, 0, 180);
  servoYPosition = constrain(servoYPosition + outputY, 0, 180);

  servoX.write(servoXPosition);
  servoY.write(servoYPosition);
}
