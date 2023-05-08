#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp280;

void setup() {
  Serial.begin(9600);
  
  if (!bmp280.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  
  // ... rest of your setup code
}
float getCurrentHeight() {
  float altitude = bmp280.readAltitude();
  return altitude;
}
