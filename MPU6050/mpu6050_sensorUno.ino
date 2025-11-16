#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("AX:");
  Serial.print(ax);
  Serial.print(",AY:");
  Serial.print(ay);
  Serial.print(",AZ:");
  Serial.print(az);
  Serial.print(",GX:");
  Serial.print(gx);
  Serial.print(",GY:");
  Serial.print(gy);
  Serial.print(",GZ:");
  Serial.println(gz);

  delay(100);
}
