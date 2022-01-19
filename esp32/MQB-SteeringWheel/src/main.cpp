#include <Arduino.h>


#define LIN_SLP 13

#include <MQB_Interface.hpp>
#include <Led_Manager.hpp>
#include <GPIO_Manager.hpp>;
// using UART 2 for LinBus
MQB_Interface mqb;
Led_Manager led;
GPIO_Manager io;
static QueueHandle_t delay_queue;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Started ");



  pinMode(LIN_SLP, OUTPUT);
  digitalWrite(LIN_SLP, HIGH);
  io.setup();
  mqb.setup();
  io.triggerPin(0);
}

void loop()
{
  mqb.loop();
  if(mqb.hasKeysPressed()){
    String key = mqb.getLastKeyString();
    Serial.println("Key Pressed " + key);
    //digitalWrite(LED_RED, LOW);   // turn the LED on (HIGH is the voltage level)
    //delay(1000);                       // wait for a second
    //digitalWrite(LED_RED, HIGH);    // turn the LED off by making the voltage LOW
  }

  

  //delay(50);
  
}
