# MPU6050 IMU Sensor Projects

This directory contains Arduino sketches for working with the MPU6050 6-axis Inertial Measurement Unit (accelerometer + gyroscope).

## Contents

### Digital Low Pass Filter (DLPF) Projects
- **MPU6050_DDLPF.ino** - Double Digital Low Pass Filter implementation
- **MPU6050_DDLPFv2.ino** - Enhanced DLPF (version 2)
- **MPU6050_DLPF_Butter.ino** - Butterworth filter integration with DLPF

### SAMD51 Platform Projects
- **MPU6050_SAMD51_XFFT.ino** - FFT analysis on SAMD51 (ARM Cortex-M4)
- **MPU6050_SAMD51_XYZread.ino** - Multi-axis data reading for SAMD51

### Gyroscope Projects
- **MPU6050_gyro_simple.ino** - Basic gyroscope reading
- **MPU6050_gyro_simpletest.ino** - Gyroscope testing and validation

### Sensor Processing
- **mpu6050_comparator.ino** - Signal comparison and threshold detection
- **mpu6050_sensorUno.ino** - Arduino Uno optimized sensor reading
- **MPU6050_Vector_Lookup.ino** - Vector-based sensor data lookup
- **mpu6050_serial_3ax.ino** - 3-axis serial output

### Documentation
- **readme.txt** - Additional documentation

## MPU6050 Overview

The MPU6050 is a popular 6-DOF IMU combining:
- 3-axis accelerometer (measures linear acceleration)
- 3-axis gyroscope (measures angular velocity)
- Built-in Digital Motion Processor (DMP)
- I2C interface for Arduino communication

## Features in These Projects

- **Filtering** - Digital filters to reduce noise and improve signal quality
- **FFT Analysis** - Frequency domain analysis of motion data
- **Multi-platform** - Support for AVR and ARM-based Arduinos
- **Signal Processing** - Butterworth filters, comparators, vector operations

## Hardware Requirements

- MPU6050 module (GY-521 or similar)
- Arduino board (Uno, Nano, SAMD51-based, etc.)
- I2C connections (SDA, SCL)
- Optional: interrupt pin for DMP operations

## Common Applications

- Motion tracking and gesture recognition
- Drone/quadcopter stabilization
- Robot balance and orientation
- Vibration analysis
- Activity monitoring

## Wiring

Typical MPU6050 I2C connections:
- VCC → 3.3V or 5V (check your module)
- GND → GND
- SDA → A4 (Uno) or SDA pin
- SCL → A5 (Uno) or SCL pin
- INT → Digital pin (optional, for interrupts)

## Notes

- Calibration is essential for accurate readings
- Use appropriate pull-up resistors for I2C (often built into modules)
- DLPF settings affect both noise reduction and response time
- SAMD51 projects leverage the ARM processor's DSP capabilities
