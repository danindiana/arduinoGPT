# arduinoGPT

A collection of Arduino projects exploring various microcontroller applications, from signal processing and sensor integration to machine learning and cryptography.

## Repository Structure

### 🔧 Microcontroller-Specific Projects

#### [atmega328p/](atmega328p/)
Projects optimized for ATmega328P-based boards (Uno, Nano, Pro Mini)
- Fast Fourier Transform implementations
- Mandelbrot set generators
- System diagnostics

#### [328p_SRAM/](328p_SRAM/)
SRAM testing and enhanced memory management for ATmega328P

#### [atmega32u4/](atmega32u4/)
Projects for ATmega32U4-based boards (Leonardo, Pro Micro)

#### [RenesasRA4M1UNOR4/](RenesasRA4M1UNOR4/)
Arduino UNO R4 specific projects (Renesas RA4M1 processor)

#### [nano33iot/](nano33iot/)
Arduino Nano 33 IoT projects (SAMD21 + WiFi/Bluetooth)

### 📡 Sensor Integration

#### [MPU6050/](MPU6050/)
6-axis IMU projects with accelerometer and gyroscope
- Digital filtering (DLPF, Butterworth)
- FFT analysis
- Motion tracking and stabilization

#### [MPU9250/](MPU9250/)
9-axis IMU projects (accelerometer, gyroscope, magnetometer)

### 🎯 Laser Control Systems

#### [laser_projects/](laser_projects/)
Comprehensive laser guidance and tracking systems
- PID-based control algorithms
- Sensor fusion (IMU, pressure, encoders)
- Data transmission via laser modulation
- Auto-tuning capabilities

### 🔢 Signal Processing & Analysis

#### [FFT/](FFT/)
Fast Fourier Transform implementations
- Entropy analysis via FFT
- Frequency domain signal processing
- Multiple platform support

### 🎲 Randomness & Cryptography

#### [entropy/](entropy/)
Random number generation and entropy harvesting
- Hardware-based entropy sources
- Password generators
- Cryptographic applications

### 🧠 Machine Learning

#### [neural_network/](neural_network/)
SmallNet - Lightweight neural networks for embedded systems
- Multiple implementation variants
- Memory-optimized designs
- Real-time inference

### 🔐 Cryptography

#### [HCgorillaCipherPipe/](HCgorillaCipherPipe/)
Cipher implementations and cryptographic pipelines

#### [bobsally/](bobsally/)
Cryptographic projects (likely Alice/Bob encryption demonstrations)

### 🛠️ Utilities & Tools

#### [utilities/](utilities/)
Development and diagnostic tools
- Memory usage monitoring (AVR, SAMD51)
- Watchdog timer implementations
- System diagnostics

#### [misc/](misc/)
Experimental and miscellaneous projects

#### [tests/](tests/)
Test suites and validation code

## Key Features

- **Multi-Platform Support** - AVR, ARM Cortex-M0+, M4, Renesas RA4M1
- **Advanced Algorithms** - FFT, PID control, neural networks, filtering
- **Sensor Fusion** - IMU, pressure, encoders, temperature
- **Signal Processing** - Digital filters, frequency analysis
- **Embedded ML** - Neural networks on microcontrollers
- **Cryptography** - Entropy generation, ciphers, secure random numbers
- **Real-Time Systems** - PID control, motion tracking, stabilization

## Hardware Platforms

- **AVR** - ATmega328P, ATmega32U4, ATmega2560
- **ARM Cortex-M0+** - SAMD21 (Arduino Zero, Nano 33 IoT)
- **ARM Cortex-M4** - SAMD51 (Adafruit Metro M4, etc.)
- **Renesas** - RA4M1 (Arduino UNO R4)

## Getting Started

1. Clone this repository
2. Navigate to the project folder of interest
3. Read the folder's README for specific requirements
4. Open the .ino file in Arduino IDE
5. Install required libraries (see individual READMEs)
6. Upload to your Arduino board

## Common Libraries Used

- Wire (I2C communication)
- SPI (Serial Peripheral Interface)
- Adafruit sensor libraries
- PID control libraries
- FFT libraries (arduinoFFT, etc.)

## Safety Notes

⚠️ **Laser Projects**: Always follow proper laser safety protocols. Use appropriate eye protection and ensure compliance with local regulations.

⚠️ **Cryptography**: Microcontroller-based entropy and cryptography have limitations. Review code carefully before using in security-critical applications.

## Contributing

Contributions are welcome! Please:
1. Document your code thoroughly
2. Add README files for new folders
3. Follow existing naming conventions
4. Test on target hardware before submitting

## License

Please check individual project files for licensing information.

## Project Origins

This repository contains projects generated with assistance from various AI tools (GPT-4, Claude, etc.) as well as community contributions and original implementations.

## Additional Resources

- [Arduino Official Documentation](https://www.arduino.cc/reference/en/)
- [ATmega328P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
- [MPU6050 Datasheet](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/)
