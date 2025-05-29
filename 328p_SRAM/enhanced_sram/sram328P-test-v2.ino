#define TEST_SIZE 256  // Test buffer size (less than total SRAM)
#define MAX_ERRORS 5   // Max errors to display per test

uint8_t* testBuffer;

void printHex(uint8_t value) {
  if (value < 0x10) Serial.print('0');
  Serial.print(value, HEX);
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Print header
  Serial.println(F("\n=== Enhanced SRAM Test Suite ==="));
  Serial.println(F("MCU: ATmega328P"));
  Serial.print(F("SRAM Available: "));
  Serial.print(freeMemory());
  Serial.println(F(" bytes (before allocation)"));
  Serial.print(F("Test Buffer Size: "));
  Serial.print(TEST_SIZE);
  Serial.println(F(" bytes"));
  
  // Allocate test buffer
  Serial.println(F("\n[1] Allocating test buffer..."));
  testBuffer = (uint8_t*)malloc(TEST_SIZE);
  if (!testBuffer) {
    Serial.println(F("ERROR: Memory allocation failed!"));
    Serial.println(F("Test aborted."));
    while (1);
  }
  Serial.print(F("Allocation successful. Free memory: "));
  Serial.print(freeMemory());
  Serial.println(F(" bytes"));

  bool overallPass = true;
  
  // Basic pattern tests
  const uint8_t patterns[] = {
    0x00, 0xFF,               // All zeros/all ones
    0xAA, 0x55,               // Alternating bits
    0xF0, 0x0F,               // Nybble patterns
    0x01, 0x02, 0x04, 0x08,   // Walking ones
    0x10, 0x20, 0x40, 0x80,
    0xFE, 0xFD, 0xFB, 0xF7,   // Walking zeros
    0xEF, 0xDF, 0xBF, 0x7F
  };
  
  Serial.println(F("\n[2] Running pattern tests..."));
  for (uint8_t p = 0; p < sizeof(patterns); p++) {
    Serial.print(F("\nPattern 0x"));
    printHex(patterns[p]);
    Serial.print(F(": "));
    
    // Write pattern
    for (int i = 0; i < TEST_SIZE; i++) {
      testBuffer[i] = patterns[p];
    }
    
    // Verify pattern
    bool patternPass = true;
    int errorCount = 0;
    for (int i = 0; i < TEST_SIZE; i++) {
      if (testBuffer[i] != patterns[p]) {
        if (errorCount < MAX_ERRORS) {
          Serial.print(F("\nError at 0x"));
          printHex(i);
          Serial.print(F(": Exp=0x"));
          printHex(patterns[p]);
          Serial.print(F(" Got=0x"));
          printHex(testBuffer[i]);
        }
        patternPass = false;
        errorCount++;
      }
    }
    
    if (patternPass) {
      Serial.println(F("OK"));
    } else {
      Serial.print(F("\nFAIL ("));
      Serial.print(errorCount);
      Serial.println(F(" errors)"));
      if (errorCount > MAX_ERRORS) {
        Serial.print(F("(First "));
        Serial.print(MAX_ERRORS);
        Serial.println(F(" errors shown)"));
      }
    }
    overallPass &= patternPass;
  }

  // Address line test
  Serial.println(F("\n[3] Running address line test..."));
  bool addrPass = true;
  int addrErrors = 0;
  
  // Write unique values to each location
  for (int i = 0; i < TEST_SIZE; i++) {
    testBuffer[i] = (uint8_t)(i & 0xFF);
  }
  
  // Verify values
  for (int i = 0; i < TEST_SIZE; i++) {
    uint8_t expected = (uint8_t)(i & 0xFF);
    if (testBuffer[i] != expected) {
      if (addrErrors < MAX_ERRORS) {
        Serial.print(F("Addr error at 0x"));
        printHex(i);
        Serial.print(F(": Exp=0x"));
        printHex(expected);
        Serial.print(F(" Got=0x"));
        printHex(testBuffer[i]);
        Serial.println();
      }
      addrPass = false;
      addrErrors++;
    }
  }
  
  if (addrPass) {
    Serial.println(F("Address test PASSED"));
  } else {
    Serial.print(F("Address test FAILED ("));
    Serial.print(addrErrors);
    Serial.println(F(" errors)"));
    if (addrErrors > MAX_ERRORS) {
      Serial.print(F("(First "));
      Serial.print(MAX_ERRORS);
      Serial.println(F(" errors shown)"));
    }
  }
  overallPass &= addrPass;

  // Heap fragmentation test
  Serial.println(F("\n[4] Heap fragmentation test..."));
  Serial.println(F("Allocating/deallocating multiple buffers..."));
  
  #define FRAG_TEST_SIZE 32
  #define FRAG_TEST_COUNT 5
  uint8_t* fragBuffers[FRAG_TEST_COUNT];
  bool fragPass = true;
  
  // Allocate multiple buffers
  for (int i = 0; i < FRAG_TEST_COUNT; i++) {
    fragBuffers[i] = (uint8_t*)malloc(FRAG_TEST_SIZE);
    if (!fragBuffers[i]) {
      Serial.print(F("Failed to allocate buffer "));
      Serial.println(i);
      fragPass = false;
    }
  }
  
  // Free every other buffer
  for (int i = 0; i < FRAG_TEST_COUNT; i += 2) {
    free(fragBuffers[i]);
    fragBuffers[i] = NULL;
  }
  
  // Try to allocate a larger buffer
  uint8_t* largeBuffer = (uint8_t*)malloc(FRAG_TEST_SIZE * 2);
  if (!largeBuffer) {
    Serial.println(F("Fragmentation detected!"));
    fragPass = false;
  } else {
    free(largeBuffer);
  }
  
  // Clean up remaining buffers
  for (int i = 0; i < FRAG_TEST_COUNT; i++) {
    if (fragBuffers[i]) free(fragBuffers[i]);
  }
  
  if (fragPass) {
    Serial.println(F("No fragmentation detected"));
  }
  overallPass &= fragPass;

  // Final summary
  Serial.println(F("\n=== TEST SUMMARY ==="));
  Serial.print(F("Free memory: "));
  Serial.print(freeMemory());
  Serial.println(F(" bytes"));
  
  if (overallPass) {
    Serial.println(F("ALL TESTS PASSED!"));
  } else {
    Serial.println(F("SOME TESTS FAILED!"));
  }
  
  Serial.println(F("==================="));

  // Free main test buffer
  free(testBuffer);
}

void loop() {
  // Nothing to do here
}

// Helper function to check free memory
extern unsigned int __heap_start;
extern void *__brkval;

int freeMemory() {
  int free_memory;
  if ((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__heap_start);
  } else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
  }
  return free_memory;
}
