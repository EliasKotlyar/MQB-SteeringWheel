#include <Arduino.h>
#define LED_GREEN 15
#define LED_RED 14
class Led_Manager
{
public:
    Led_Manager(void);
    void setup(void);
    void enableLed(int pintNr, bool state);   
};
