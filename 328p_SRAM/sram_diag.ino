#define INITIAL_TEST_SIZE 256  // Starting test size
#define MAX_ALLOC_ATTEMPTS 32  // For fragmentation test
#define VERIFY_DELAY 10        // ms between write and verify

uint8_t* testBuffer;

// Walking bit patterns (1 bit set at each position)
const uint8_t walkingBits[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  printHeader();
  
  // Basic pattern test
  runPatternTests();
  
  // Walking bit test
  runWalkingBitTest();
  
  // Fragmentation test
  runFragmentationTest();
  
  // Memory limit test
  runMemoryLimitTest();
  
  Serial.println(F("\n=== All Tests Complete ==="));
}

void loop() {
  // Nothing to do here
}

void printHeader() {
  Serial.println(F("\n=== Enhanced SRAM Test Suite ==="));
  Serial.println(F("MCU: ATmega328P"));
  Serial.print(F("Initial Test Buffer Size: "));
  Serial.print(INITIAL_TEST_SIZE);
  Serial.println(F(" bytes"));
  Serial.println(F("Verify Delay: 10ms"));
}

void runPatternTests() {
  Serial.println(F("\n=== Pattern Tests ==="));
  
  Serial.println(F("\nStep 1: Allocating test buffer..."));
  testBuffer = (uint8_t*)malloc(INITIAL_TEST_SIZE);
  if (!testBuffer) {
    Serial.println(F("ERROR: Failed to allocate test buffer!"));
    return;
  }
  Serial.println(F("Buffer allocated successfully."));

  // Test patterns
  const uint8_t patterns[] = {0x00, 0xFF, 0xAA, 0x55, 0xF0, 0x0F};
  const int patternCount = sizeof(patterns)/sizeof(patterns[0]);
  
  bool overallPass = true;
  
  for (int p = 0; p < patternCount; p++) {
    Serial.print(F("\nTesting Pattern 0x"));
    if (patterns[p] < 0x10) Serial.print('0');
    Serial.println(patterns[p], HEX);
    
    // Write pattern
    Serial.print(F("Writing pattern to all "));
    Serial.print(INITIAL_TEST_SIZE);
    Serial.println(F(" bytes..."));
    for (int i = 0; i < INITIAL_TEST_SIZE; i++) {
      testBuffer[i] = patterns[p];
    }
    Serial.println(F("Write complete."));
    
    // Delay between write and verify
    delay(VERIFY_DELAY);
    
    // Verify pattern
    Serial.println(F("Verifying pattern..."));
    bool patternPass = true;
    int errorCount = 0;
    
    for (int i = 0; i < INITIAL_TEST_SIZE; i++) {
      if (testBuffer[i] != patterns[p]) {
        if (errorCount < 5) {
          Serial.print(F("ERROR at byte "));
          Serial.print(i);
          Serial.print(F(": Expected 0x"));
          if (patterns[p] < 0x10) Serial.print('0');
          Serial.print(patterns[p], HEX);
          Serial.print(F(", Got 0x"));
          if (testBuffer[i] < 0x10) Serial.print('0');
          Serial.println(testBuffer[i], HEX);
        }
        patternPass = false;
        errorCount++;
      }
    }
    
    printTestResult(patternPass, errorCount);
    overallPass &= patternPass;
  }
  
  free(testBuffer);
  Serial.println(F("\nPattern Tests Complete."));
  Serial.println(overallPass ? F("OVERALL: PASS") : F("OVERALL: FAIL"));
}

void runWalkingBitTest() {
  Serial.println(F("\n=== Walking Bit Test ==="));
  
  testBuffer = (uint8_t*)malloc(INITIAL_TEST_SIZE);
  if (!testBuffer) {
    Serial.println(F("ERROR: Failed to allocate buffer!"));
    return;
  }
  
  bool overallPass = true;
  const int bitCount = sizeof(walkingBits)/sizeof(walkingBits[0]);
  
  for (int b = 0; b < bitCount; b++) {
    Serial.print(F("\nTesting bit position "));
    Serial.print(b);
    Serial.print(F(" (0x"));
    Serial.print(walkingBits[b], HEX);
    Serial.println(F(")"));
    
    // Write pattern
    for (int i = 0; i < INITIAL_TEST_SIZE; i++) {
      testBuffer[i] = walkingBits[b];
    }
    
    delay(VERIFY_DELAY);
    
    // Verify
    bool bitPass = true;
    int errorCount = 0;
    for (int i = 0; i < INITIAL_TEST_SIZE; i++) {
      if (testBuffer[i] != walkingBits[b]) {
        if (errorCount < 5) {
          Serial.print(F("ERROR at byte "));
          Serial.print(i);
          Serial.print(F(": Expected 0x"));
          Serial.print(walkingBits[b], HEX);
          Serial.print(F(", Got 0x"));
          Serial.println(testBuffer[i], HEX);
        }
        bitPass = false;
        errorCount++;
      }
    }
    
    printTestResult(bitPass, errorCount);
    overallPass &= bitPass;
  }
  
  free(testBuffer);
  Serial.println(F("\nWalking Bit Test Complete."));
  Serial.println(overallPass ? F("OVERALL: PASS") : F("OVERALL: FAIL"));
}

void runFragmentationTest() {
  Serial.println(F("\n=== Fragmentation Test ==="));
  
  uint8_t* buffers[MAX_ALLOC_ATTEMPTS];
  int successfulAllocs = 0;
  
  // Allocate multiple small buffers
  for (int i = 0; i < MAX_ALLOC_ATTEMPTS; i++) {
    buffers[i] = (uint8_t*)malloc(32);  // Try to allocate 32 bytes each time
    if (buffers[i]) {
      successfulAllocs++;
      // Write a pattern to ensure it's usable
      memset(buffers[i], i, 32);
    } else {
      break;
    }
  }
  
  // Free buffers in alternating pattern
  for (int i = 0; i < successfulAllocs; i += 2) {
    if (buffers[i]) {
      free(buffers[i]);
      buffers[i] = NULL;
    }
  }
  
  // Try to allocate a larger buffer
  uint8_t* largeBuffer = (uint8_t*)malloc(256);
  
  Serial.print(F("Successfully allocated "));
  Serial.print(successfulAllocs);
  Serial.println(F(" small buffers"));
  Serial.print(F("Large buffer allocation after fragmentation: "));
  Serial.println(largeBuffer ? F("SUCCESS") : F("FAILED"));
  
  // Cleanup
  if (largeBuffer) free(largeBuffer);
  for (int i = 0; i < successfulAllocs; i++) {
    if (buffers[i]) free(buffers[i]);
  }
}

void runMemoryLimitTest() {
  Serial.println(F("\n=== Memory Limit Test ==="));
  
  size_t size = 32;  // Start small
  int successfulAllocs = 0;
  
  while (size < 2048) {  // Max theoretical SRAM size for UNO
    Serial.print(F("Attempting to allocate "));
    Serial.print(size);
    Serial.print(F(" bytes... "));
    
    uint8_t* buf = (uint8_t*)malloc(size);
    if (buf) {
      Serial.println(F("SUCCESS"));
      successfulAllocs++;
      free(buf);
      size *= 2;  // Try doubling the size
    } else {
      Serial.println(F("FAILED"));
      break;
    }
  }
  
  Serial.print(F("\nLargest successful allocation: "));
  Serial.print(size/2);
  Serial.println(F(" bytes"));
}

void printTestResult(bool pass, int errorCount) {
  if (pass) {
    Serial.println(F("Test PASSED"));
  } else {
    Serial.print(F("Test FAILED with "));
    Serial.print(errorCount);
    Serial.println(F(" errors"));
    if (errorCount > 5) {
      Serial.println(F("(Only first 5 errors shown)"));
    }
  }
}
