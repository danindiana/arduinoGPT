# Enhanced SRAM Test Suite for Arduino Uno (ATmega328P)

![Arduino Uno](https://upload.wikimedia.org/wikipedia/commons/thumb/b/ba/Arduino_Uno_-_R3.jpg/320px-Arduino_Uno_-_R3.jpg)

A comprehensive memory testing utility for verifying SRAM integrity on ATmega328P-based boards (Arduino Uno and compatibles).

## Features

✅ **Pattern Testing** - Tests with 18 different bit patterns including:
   - All zeros (0x00) and ones (0xFF)
   - Alternating bits (0xAA, 0x55)
   - Walking ones and zeros
   - Nybble patterns (0xF0, 0x0F)

✅ **Address Line Verification** - Detects address decoder faults by writing unique values to each location

✅ **Heap Analysis** - Includes fragmentation detection and memory usage reporting

✅ **Detailed Diagnostics** - Clear error reporting with:
   - First 5 errors shown for each test
   - Hex-formatted memory dumps
   - Memory usage before/after allocation

✅ **Robust Architecture** - Proper memory allocation checking and cleanup

## Installation

1. Copy the `.ino` file to a new Arduino sketch
2. Compile and upload to your Arduino Uno
3. Open the Serial Monitor (115200 baud)

## Test Coverage

The suite verifies:

- Individual bit storage (all patterns)
- Address line integrity (no shorts between lines)
- Proper heap management
- Memory cell isolation (no coupling between adjacent cells)

## Sample Output
