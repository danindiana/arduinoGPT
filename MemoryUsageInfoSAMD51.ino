#include "FreeRTOS.h"
#include "task.h"

// MemoryUsageInfoSAMD51.ino

void setup() {
  Serial.begin(115200);
  while (!Serial);

  printMemoryInfo();
}

void loop() {
  delay(1000);
  printMemoryInfo();
}

void printMemoryInfo() {
  // print total free heap memory
  Serial.print("Free heap size: ");
  Serial.println(xPortGetFreeHeapSize());

  // print minimum free heap memory
  Serial.print("Min free heap size: ");
  Serial.println(xPortGetMinimumEverFreeHeapSize());
}
