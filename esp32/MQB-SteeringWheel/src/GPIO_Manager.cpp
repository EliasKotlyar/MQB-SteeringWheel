#include "GPIO_Manager.hpp"

GPIO_Manager::GPIO_Manager(void)
{
}
void GPIO_Manager::setup(void)
{
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
}

void GPIO_Manager::triggerPin(byte pinNr)
{
  byte x = 0;
  bitSet(x, pinNr);
  this->setPin(x);
  delay(50);
  this->setPin(0);
}
void GPIO_Manager::setPin(byte data)
{
  digitalWrite(PIN_LATCH, LOW);
  shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, data);
  digitalWrite(PIN_LATCH, HIGH);
}