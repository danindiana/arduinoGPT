# Utilities and Diagnostic Tools

This directory contains utility sketches for memory diagnostics, system monitoring, and general-purpose tools for Arduino development.

## Contents

### Memory Diagnostics
- **MemoryUsageInfo.ino** - General memory usage reporting utility
- **MemoryUsageInfoAVR.ino** - AVR-specific memory diagnostics (ATmega series)
- **MemoryUsageInfoSAMD51.ino** - SAMD51-specific memory diagnostics (ARM Cortex-M4)
- **MemoryUsageInfo.txt** - Documentation and output examples

### System Utilities
- **watchdog_rev1** - Watchdog timer implementation for system stability

## Memory Usage Tools

The memory diagnostic sketches help developers:
- Monitor available RAM during runtime
- Detect memory leaks
- Optimize memory usage
- Understand stack and heap allocation
- Plan resource usage for complex projects

### Platform Support
- **AVR** - ATmega328P, ATmega2560 (Uno, Mega, Nano, etc.)
- **SAMD51** - ARM Cortex-M4 based boards (Adafruit Metro M4, etc.)

## Watchdog Timer

The watchdog implementation provides:
- Automatic system reset on hang/freeze
- Configurable timeout periods
- System reliability improvement
- Debug output before reset

## Usage

Include these utilities in your development workflow to:
1. Baseline memory usage of your projects
2. Identify memory-intensive operations
3. Prevent system crashes due to memory exhaustion
4. Improve code reliability with watchdog protection

## Notes

- Memory reporting varies by architecture
- Always test watchdog timers carefully to avoid unwanted resets
- Use appropriate version for your target platform
