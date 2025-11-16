# ATmega328P Projects

This directory contains Arduino sketches specifically designed for the ATmega328P microcontroller (Arduino Uno, Nano, Pro Mini, etc.).

## Contents

### Fast Fourier Transform Projects
- **328P_Ffourierv1.ino** - Initial FFT implementation
- **328p_Ffourierv2.ino** - FFT version 2 with improvements
- **328p_Ffourierv3Rand.ino** - FFT with random data generation
- **328p_Ffourierv4Rand.ino** - Enhanced FFT with random inputs
- **Create 328p_Ffv5RandSP.ino** - FFT v5 with serial port output
- **Create 328p_Ffv6RandSP.ino** - FFT v6 with serial port enhancements

### Mandelbrot Set Generators
- **328p_mandelbrot_hres.ino** - High-resolution Mandelbrot set generator
- **328p_mandelbrot_serial.ino** - Mandelbrot with serial output
- **328p_mandlebrot.ino** - Basic Mandelbrot implementation

### Diagnostics
- **328p_diagnostics.ino** - System diagnostics sketch
- **328p_diagnostic.txt** - Diagnostic output log

## Hardware Requirements
- ATmega328P-based Arduino board (Uno, Nano, Pro Mini)
- Sufficient RAM for FFT operations (2KB SRAM)
- Serial connection for output monitoring

## Notes
- These sketches are optimized for the 328P's limited resources
- FFT projects may require careful memory management
- Some projects output data via serial for visualization
