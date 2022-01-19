#include <Arduino.h>
#define PIN_LATCH 16 // SHIFT_SHCP
#define PIN_CLOCK 17 // SHIFT_STCP
#define PIN_DATA 18 // SHIFT_DS
class GPIO_Manager
{
public:
    GPIO_Manager(void);
    void setup(void);
    void triggerPin(byte pinNr);
    void setPin(byte data);
};
