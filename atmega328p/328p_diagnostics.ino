#include <avr/wdt.h>

#define TEST_PIN_1 2
#define TEST_PIN_2 3

void setup() {
  Serial.begin(9600);

  pinMode(TEST_PIN_1, OUTPUT);
  pinMode(TEST_PIN_2, INPUT);

  wdt_enable(WDTO_2S);
}

void loop() {
  // Test GPIO
  digitalWrite(TEST_PIN_1, HIGH);
  delay(1); // Give the signal time to propagate
  if (digitalRead(TEST_PIN_2) != HIGH) {
    Serial.println("GPIO test failed!");
  }
  digitalWrite(TEST_PIN_1, LOW);
  delay(1); // Give the signal time to propagate
  if (digitalRead(TEST_PIN_2) != LOW) {
    Serial.println("GPIO test failed!");
  }

  // Test ADC
  int adcValue = analogRead(A0);
  Serial.print("ADC value: ");
  Serial.println(adcValue);

  // Test serial loopback
  Serial.println("Testing serial loopback. Please connect RX and TX...");
  delay(1000);
  Serial.write('T');
  delay(10);
  if (Serial.available()) {
    char c = Serial.read();
    if (c != 'T') {
      Serial.println("Serial loopback test failed!");
    }
  }

  // Test watchdog timer
  Serial.println("Testing watchdog timer. The system should reset...");
  delay(3000); // Wait for longer than the watchdog timeout

  wdt_reset();

  delay(1000);
}
