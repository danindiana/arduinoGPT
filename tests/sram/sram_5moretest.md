# Safe SRAM Test Code Examples for ATmega328P

Here are five safe and practical examples demonstrating SRAM usage on the ATmega328P:

## 1. Simple Variable Storage
```c
#include <avr/io.h>

void test_variable_storage() {
    // Global variables (stored in data section of SRAM)
    static uint8_t global_var = 100;
    
    // Local variables (stored on stack)
    uint8_t local_var = 50;
    uint16_t another_var = local_var * 2;
    
    // Volatile variable (ensures compiler doesn't optimize it away)
    volatile uint8_t sensor_value = analogRead(0) >> 2;
}

int main(void) {
    test_variable_storage();
    return 0;
}
```

## 2. Function Call Stack Usage
```c
#include <avr/io.h>

uint8_t calculate(uint8_t a, uint8_t b) {
    uint8_t result = a + b;  // Local variable on stack
    return result;
}

void stack_demo() {
    uint8_t x = 10;
    uint8_t y = 20;
    uint8_t sum = calculate(x, y);  // Function call uses stack
    
    // Verify stack didn't corrupt our locals
    if (x != 10 || y != 20) {
        // Handle error
    }
}

int main(void) {
    stack_demo();
    return 0;
}
```

## 3. Buffer Initialization and Access
```c
#include <avr/io.h>
#include <string.h>

#define BUF_SIZE 32

void buffer_demo() {
    // Static buffer initialization
    static uint8_t static_buffer[BUF_SIZE];
    
    // Stack buffer with initialization
    uint8_t stack_buffer[BUF_SIZE] = {0};  // Zero-initialized
    
    // Safe string copy
    const char* message = "Hello";
    strncpy((char*)stack_buffer, message, BUF_SIZE - 1);
    stack_buffer[BUF_SIZE - 1] = '\0';  // Ensure null termination
    
    // Safe buffer access
    for (uint8_t i = 0; i < BUF_SIZE; i++) {
        static_buffer[i] = stack_buffer[i];
    }
}

int main(void) {
    buffer_demo();
    return 0;
}
```

## 4. Pointer Arithmetic
```c
#include <avr/io.h>

#define ARRAY_SIZE 10

void pointer_demo() {
    uint8_t data[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t* ptr = data;  // Pointer to array start
    
    // Safe pointer arithmetic
    for (uint8_t i = 0; i < ARRAY_SIZE; i++) {
        uint8_t value = *(ptr + i);  // Equivalent to data[i]
        // Do something with value
    }
    
    // Pointer bounds checking
    uint8_t* end = data + ARRAY_SIZE;
    for (ptr = data; ptr < end; ptr++) {
        *ptr = 0xFF;  // Safe because we checked bounds
    }
}

int main(void) {
    pointer_demo();
    return 0;
}
```

## 5. Recursive Function with Stack Management
```c
#include <avr/io.h>

#define MAX_RECURSION_DEPTH 10

void recursive_function(uint8_t depth) {
    // Local variable on stack for each recursion level
    uint8_t local_data[8] = {depth, depth+1, depth+2, depth+3, 
                            depth+4, depth+5, depth+6, depth+7};
    
    // Base case to prevent stack overflow
    if (depth >= MAX_RECURSION_DEPTH) {
        return;
    }
    
    // Do something with local_data
    for (uint8_t i = 0; i < sizeof(local_data); i++) {
        local_data[i] += 1;
    }
    
    // Recursive call
    recursive_function(depth + 1);
    
    // Verify our local data wasn't corrupted
    for (uint8_t i = 0; i < sizeof(local_data); i++) {
        if (local_data[i] != (depth + i + 1)) {
            // Handle stack corruption error
            return;
        }
    }
}

int main(void) {
    recursive_function(0);
    return 0;
}
```

## Safety Considerations:

1. **Bounded Operations**: All array/pointer operations stay within declared bounds
2. **Stack Management**: Recursion is limited to prevent overflow
3. **Memory Initialization**: Buffers are properly initialized
4. **Volatile Usage**: Used where needed to prevent optimization issues
5. **Error Checking**: Includes basic checks for stack corruption
6. **Non-blocking**: All examples run quickly without delays

These examples demonstrate safe SRAM usage patterns while avoiding common pitfalls like buffer overflows, stack overflows, and undefined behavior.
