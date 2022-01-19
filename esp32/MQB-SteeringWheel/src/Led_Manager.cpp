#include "Led_Manager.hpp";

Led_Manager::Led_Manager(void){

}
void Led_Manager::setup(void)
{
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);  
  digitalWrite(LED_RED, HIGH);
}

void Led_Manager::enableLed(int pintNr, bool state){
    digitalWrite(pintNr, state);  
}
