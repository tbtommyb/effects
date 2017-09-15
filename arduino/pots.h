#define NUM_CTRLS 2
#define CTRL_ON_BIT 10
#define CTRL_OFF 0
#define DEBOUNCE_TIME 1000  // microseconds

#define ID_TAG(id) ((id) << 12)
#define LOW_BYTE(w) ((uint8_t) ((w) & 0xff))
#define HIGH_BYTE(w) ((uint8_t) ((w) >> 8))
#define BUTTON_PORT (PORTD)
#define BUTTON_PIN (PIND)

typedef struct _Button Button;
typedef struct _Pot Pot;
typedef struct _Control Control;

Control newControl(uint16_t i);
uint16_t pollPot(Pot pot);
bool isPressed(Button btn);
void initADC(void);
uint16_t readADC(uint8_t channel);
uint8_t debounce(uint8_t pin);
void transmitCtrlValue(Control ctrl);
void transmitCtrlOff(Control ctrl);
void transmitWord(uint16_t value);
