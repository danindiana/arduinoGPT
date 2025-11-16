# Laser Control and Tracking Projects

This directory contains Arduino projects for laser guidance, tracking, and data transmission systems, primarily designed for Arduino Mega boards.

## Contents

### Data Transmission
- **Laser_Data_transmit.ino** - Transmit data via laser modulation
- **laser_Data_receive.ino** - Receive and decode laser-transmitted data

### PID Control Systems
- **laser_impact_PIDALGO.ino** - Laser impact control using PID algorithm
- **laser_impact_offset.ino** - Offset compensation for laser targeting
- **laser_offset_PIDRTtune.ino** - Real-time PID tuning for laser control
- **laser_offset_PID_MPU6050.ino** - PID control integrated with MPU6050 IMU
- **lsr_ofst_MPUPIDautotune.ino** - Auto-tuning PID with MPU6050

### Sensor Integration
- **laser_offset_BMP280.ino** - Laser control with BMP280 pressure/altitude sensor
- **laser_offset_encoder.ino** - Encoder-based position feedback
- **laser_offset_moveToOffsetIndicator.ino** - Visual offset indication system

### MEGA Projects
- **MEGA_Laser_guide2target.ino** - Laser guidance to target system
- **MEGA_laser_FlyerV2.ino** - Advanced laser tracking (version 2)
- **Mega_Laser_Flyer.ino** - Original laser tracking implementation

### Documentation
- **Arduino_Mega_Laser_detect.txt** - Laser detection documentation
- **MEGA_laser_Flyer_psedcode.txt** - Pseudocode for laser flyer system

## Hardware Requirements
- Arduino Mega 2560 (recommended for most projects)
- Laser module (transmitter/detector)
- MPU6050 IMU sensor (for stabilization projects)
- BMP280 sensor (for altitude-aware projects)
- Rotary encoders (for position feedback)
- Servo motors for laser positioning

## Features
- PID-based closed-loop control
- IMU sensor fusion for stabilization
- Data transmission via laser modulation
- Auto-tuning capabilities
- Multi-sensor integration

## Safety Warning
⚠️ **Laser Safety**: Always follow proper laser safety protocols. Use appropriate eye protection and ensure compliance with local regulations regarding laser power and operation.
