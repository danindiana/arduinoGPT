#include <avr/wdt.h>
#include <avr/interrupt.h>

volatile uint32_t random_number = 0;
volatile uint8_t random_bits = 0;

void setup() {
  Serial.begin(9600);

  // Configure the watchdog timer
  wdt_reset();
  cli();
  MCUSR = 0;
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = (1 << WDIE) | (1 << WDP2) | (1 << WDP0); // Set to interrupt mode, with 250ms timeout
  sei();
}

void loop() {
  if (random_bits >= 32) {
    Serial.println(random_number, DEC);
    random_bits = 0;
    random_number = 0;
  }
}

// Watchdog timer interrupt service routine
ISR(WDT_vect) {
  static uint32_t last_micros = 0;

  uint32_t now_micros = micros();
  uint32_t time_diff = now_micros - last_micros;
  last_micros = now_micros;

  // XOR the least significant bit of the time difference with the current random number
  random_number ^= (time_diff & 1) << random_bits;

  random_bits++;
}
