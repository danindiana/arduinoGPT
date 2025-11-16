# SmallNet - Neural Network Projects

This directory contains implementations of small neural networks designed to run on resource-constrained Arduino microcontrollers.

## Contents

### Core Implementations
- **smallnet** - Basic neural network implementation in C
- **smallnet_minimalist** - Minimalist version with reduced features
- **smallnetstdlib** - Implementation using standard library functions
- **smallnetiostream** - Version with I/O stream support

### Random Output Variants
- **smallnet_randomserialout** - Neural network with random serial output
- **smallnet_randomserialout_rev2** - Enhanced random output (revision 2)
- **smallnet_randomserialout_rev3** - Further improvements (revision 3)

## Overview

SmallNet is a lightweight neural network framework designed for embedded systems. These implementations focus on:

- **Memory Efficiency** - Optimized for microcontrollers with limited RAM
- **Performance** - Fast inference suitable for real-time applications
- **Flexibility** - Multiple variants for different use cases

## Features

- Forward propagation
- Simplified activation functions
- Serial output for monitoring and debugging
- Minimal dependencies
- Low memory footprint

## Use Cases

- Pattern recognition on embedded devices
- Sensor data classification
- Simple decision-making systems
- Educational demonstrations of neural networks on microcontrollers

## Hardware Requirements

- Arduino board with sufficient RAM (recommend 2KB+)
- Serial connection for output monitoring
- Varies by specific implementation

## Notes

- These are simplified neural network implementations
- Not suitable for complex deep learning tasks
- Ideal for learning and prototyping on embedded systems
