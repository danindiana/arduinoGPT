float targetX = 0;   // Target X position defined by the offset indicator
float targetY = 0;   // Target Y position defined by the offset indicator
float kP = 0.1;      // Proportional control gain

void moveToOffsetIndicator() {
  // Get the current position of the canister (replace with appropriate methods)
  float currentX = getCurrentX();
  float currentY = getCurrentY();

  // Calculate the error between the current position and the target position
  float errorX = targetX - currentX;
  float errorY = targetY - currentY;

  // Calculate the control signal using proportional control
  float controlSignalX = kP * errorX;
  float controlSignalY = kP * errorY;

  // Update the servo positions (make sure to limit the positions between 0 and 180 degrees)
  servoXPosition = constrain(servoXPosition + controlSignalX, 0, 180);
  servoYPosition = constrain(servoYPosition + controlSignalY, 0, 180);

  servoX.write(servoXPosition);
  servoY.write(servoYPosition);
}
