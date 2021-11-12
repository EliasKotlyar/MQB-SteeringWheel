#include <Arduino.h>

#define LED_BUILTIN 25
#define LIN_SLP 21

#include <MQB_Interface.hpp>
// using UART 2 for LinBus
MQB_Interface mqb;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LIN_SLP, OUTPUT);
  digitalWrite(LIN_SLP, HIGH);
  mqb.setup();
}

void loop()
{
  mqb.loop();
  if(mqb.hasKeysPressed()){
    String key = mqb.getLastKeyString();
    Serial.println("Key Pressed " + key);
  }
  

  delay(50);
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);                       // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}
