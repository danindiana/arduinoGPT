// MemoryUsageInfo.ino

extern char *__bss_end;
extern char *__data_start;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  printMemoryInfo();
}

void loop() {
  delay(1000);
  printMemoryInfo();
}

void printMemoryInfo() {
  int stackTop;
  int heapTop;
  
  // Get current position of the stack
  stackTop = (int) &stackTop;

  // Get current position of heap
  #ifdef ESP8266
    // ESP8266 uses "ESP" namespace
    heapTop = (int) ESP.getFreeHeap();
  #else
    heapTop = (int) &__bss_end;
  #endif

  Serial.print("Stack size: ");
  Serial.println(stackTop - heapTop);

  Serial.print("Heap size: ");
  Serial.println(heapTop - (int) &__data_start);

  Serial.print(".data + .bss size: ");
  Serial.println((int)&__bss_end - (int)&__data_start);

  Serial.println();
}
