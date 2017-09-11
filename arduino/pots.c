// Read in potentiometer value
// Code based on this:
// https://github.com/hexagon5un/AVR-Programming/blob/master/Chapter07_Analog-to-Digital-Conversion-I/nightLight/

// TODO: add support for buttons to toggle controls

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

#define ADC0 PINC0
#define ADC1 PINC1
#define ADC2 PINC2
#define ADC3 PINC3

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

typedef struct {
  uint8_t pin;
  uint16_t val;
} Pot;

Pot newPot(uint8_t pin) {
  Pot pot;
  pot.pin = pin;
  pot.val = 0;
  return pot;
}

void initADC(void) {
  ADMUX |= (1 << REFS0);                 // reference voltage on AVCC
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // ADC clock prescaler /8
  ADCSRA |= (1 << ADEN);                 // enable ADC
}

uint16_t readADC(uint8_t channel) {
  ADMUX = (0xf0 & ADMUX) | channel;      // set bottom four bits (the multiplexer)
  ADCSRA |= (1 << ADSC);                 // start conversion
  loop_until_bit_is_clear(ADCSRA, ADSC); // wait until conversion is done
  return (ADC);
}

void pollPot(Pot pot) {
  uint16_t val = readADC(pot.pin);
  if (val != pot.val) {
    pot.val = val;
    uint16_t output = pot.val | (pot.pin << 12); // move pin number up to top four bits
    transmitByte(lowByte(output));               // USART transmits LSB -> MSB
    transmitByte(highByte(output));
  }
}

int main(void) {
  // -------- Inits --------- //
  Pot ADC0_pot = newPot(ADC0);
  Pot ADC1_pot = newPot(ADC1);

  initADC();

  // -------- Main loop -------- //
  while(1) {
    pollPot(ADC0_pot);
    pollPot(ADC1_pot);

    _delay_ms(20);
  }
  return 0;
}
