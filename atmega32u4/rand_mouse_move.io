#include <Mouse.h>

void setup() {
  Serial.begin(9600); // Initialize serial communication
  delay(4000); // Wait for 4 seconds
  
  Serial.println("Starting random mouse movements and random walk...");

  // Perform random mouse movements in three axes
  for (int i = 0; i < 100; i++) {
    int xMovement = random(-10, 11); // Random movement along X-axis (-10 to 10)
    int yMovement = random(-10, 11); // Random movement along Y-axis (-10 to 10)
    int scrollMovement = random(-10, 11); // Random scroll movement (-10 to 10)

    Mouse.move(xMovement, yMovement, scrollMovement);
    delay(50); // Delay between movements
  }

  Serial.println("Random mouse movements complete.");

  // Perform random walk in two dimensions
  int x = 0;
  int y = 0;

  Serial.println("Starting random walk in two dimensions...");

  for (int i = 0; i < 100; i++) {
    int direction = random(4); // Randomly select direction (0: up, 1: down, 2: left, 3: right)

    switch(direction) {
      case 0: // Up
        y++;
        break;
      case 1: // Down
        y--;
        break;
      case 2: // Left
        x--;
        break;
      case 3: // Right
        x++;
        break;
    }

    Mouse.move(x, y); // Move the mouse cursor
    delay(50); // Delay between movements
  }

  Serial.println("Random walk complete.");

  Serial.println("Program execution complete.");
}

void loop() {
  // Empty loop, as we only want the setup function to run once
}
