/*
Read in potentiometer value
Code based on this:
https://github.com/hexagon5un/AVR-Programming/blob/master/Chapter07_Analog-to-Digital-Conversion-I/nightLight/

Output is in the following 16 bit format:

0000 00 0000000000
\    \  \
 \    \  10 bit ADC value
  \    01 indicates ON, ten lowest bits will be latest ADC value
   \   00 indicates OFF, ten lowest bits will be empty
    Four bit control identifier, start from 0000

There will be no output until a control is turned on. It will not output again
until its potentiometer value changes or it is turned off:

0011010000000000 <- ctrl 3 is ON and has value 0
0011010000000111 <- ctrl 3 is ON and has value 7
0011000000000000 <- ctrl 3 is OFF. Output from ctrl 3 will now stop
0011011111111111 <- ctrl 3 is ON and has value 0x3FF

*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include "USART.h"
#include "pots.h"

const uint8_t POT_PINS[NUM_CTRLS] = { PINC0, PINC1 };
const uint8_t BUTTON_PINS[NUM_CTRLS] = { PIND4, PIND5 };

struct _Button {
  uint8_t pin;
  bool is_pressed;
};

struct _Pot {
  uint8_t pin;
  uint16_t val;
};

struct _Control {
  Button* btn;
  Pot* pot;
  bool is_on;
  uint16_t id;
};

Control* newControl(uint16_t i) {
  Button *btn = malloc(sizeof(Button));
  btn->pin = BUTTON_PINS[i];
  btn->is_pressed = false;

  Pot *pot = malloc(sizeof(Pot));
  pot->pin = POT_PINS[i];
  pot->val = 0;

  Control *ctrl = malloc(sizeof(Control));
  ctrl->btn = btn;
  ctrl->pot = pot;
  ctrl->is_on = false;
  ctrl->id = i;

  return ctrl;
}

// ADC

void initADC(void) {
  ADMUX |= (1 << REFS0);                 // reference voltage on AVCC
  ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // ADC clock prescaler /128
  ADCSRA |= (1 << ADEN);                 // enable ADC
}

uint16_t readADC(uint8_t pin) {
  ADMUX = (MUX_MASK & ADMUX) | pin;      // set bottom five bits (the multiplexer)
  ADCSRA |= (1 << ADSC);                 // start conversion
  loop_until_bit_is_clear(ADCSRA, ADSC); // wait until conversion is done
  return (ADC);
}

// Buttons

bool debounce(uint8_t pin) {
  if (bit_is_clear(BUTTON_PIN, pin)) {      // button is pressed now
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, pin)) {    // still pressed
      return true;
    }
  }
  return false;
}

bool isPressed(Button* btn) {
  if (debounce(btn->pin)) {
    return true;
  }
  return false;
}

// Transmitting messages

void transmitOnMessage(Control* ctrl) {
  // Submit ctrl ID in top four, ON bit set and pot value in bottom ten
  uint16_t output = ID_TAG(ctrl->id) | (1 << CTRL_ON_BIT) | ctrl->pot->val;
  transmitWord(output);
}

void transmitOffMessage(Control* ctrl) {
  // Submit ctrl ID top four bits, rest empty
  uint16_t output = ID_TAG(ctrl->id) | CTRL_OFF;
  transmitWord(output);
}

void transmitWord(uint16_t value) {
  transmitByte(LOW_BYTE(value)); // USART transmits LSB -> MSB
  transmitByte(HIGH_BYTE(value));
}

int main(void) {
  // -------- Inits --------- //
  Control* controls[NUM_CTRLS];
  for (uint16_t i = 0; i < NUM_CTRLS; i++) {
    Control *ctrl = newControl(i);
    controls[i] = ctrl;
    BUTTON_PORT |= (1 << ctrl->btn->pin); // enable pull-up resistor on button pin
  }

  initADC();
  initUSART();

  // -------- Main loop -------- //
  while (1) {

    for (uint8_t i = 0; i < NUM_CTRLS; i++) {
      Control* ctrl = controls[i];

      uint16_t currentPotValue = readADC(ctrl->pot->pin);
      if (abs(currentPotValue - ctrl->pot->val) > 2) {
      // Record new pot value
        ctrl->pot->val = currentPotValue;
        if (ctrl->is_on) {
          transmitOnMessage(ctrl);
        }
      }

      if (isPressed (ctrl->btn)) {
        if (ctrl->btn->is_pressed == false) {
          // Button wasn't pressed last time so toggle ctrl and transmit change
          ctrl->btn->is_pressed = true;
          ctrl->is_on = !ctrl->is_on;
          if (ctrl->is_on) {
            transmitOnMessage(ctrl);
          } else {
            transmitOffMessage(ctrl);
          }
        }
        // Button is being held down so do nothing here
      } else {
        // To handle when the button has been let go
        ctrl->btn->is_pressed = false;
      }
    }
    _delay_ms(20);
  }
  return 0;
}
