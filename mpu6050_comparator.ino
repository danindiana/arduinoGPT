//Ref https://github.com/ElectronicCats/mpu6050

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if (Serial1.available()) {
    String data = Serial1.readStringUntil('\n');
    int16_t ax, ay, az, gx, gy, gz;
    sscanf(data.c_str(), "AX:%d,AY:%d,AZ:%d,GX:%d,GY:%d,GZ:%d", &ax, &ay, &az, &gx, &gy, &gz);

    // Comparison logic goes here.
    // For example, compare the accelerometer readings to predefined threshold values.
    int16_t ax_threshold = 1000;
    int16_t ay_threshold = 1000;
    int16_t az_threshold = 1000;

    if (abs(ax) > ax_threshold || abs(ay) > ay_threshold || abs(az) > az_threshold) {
      Serial.println("Accelerometer threshold exceeded");
    }
    
    // Similarly, compare gyroscope readings to predefined threshold values.
    int16_t gx_threshold = 1000;
    int16_t gy_threshold = 1000;
    int16_t gz_threshold = 1000;

    if (abs(gx) > gx_threshold || abs(gy) > gy_threshold || abs(gz) > gz_threshold) {
      Serial.println("Gyroscope threshold exceeded");
    }
  }
}
