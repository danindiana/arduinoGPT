#include <Arduino.h>

extern int __heap_start, *__brkval; 

int getFreeRam () {
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Free RAM: ");
  Serial.println(getFreeRam());

  int stackTop;
  int heapTop = (int)__brkval == 0 ? (int)&__heap_start : (int)__brkval;
  Serial.print("Stack size: ");
  Serial.println((int)&stackTop - heapTop);

  Serial.print(".data + .bss size: ");
  Serial.println((int)&_end - (int)&__data_start);

  delay(5000); // delay between prints
}
