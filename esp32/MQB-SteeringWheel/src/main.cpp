#include <Arduino.h>

#define LED_BUILTIN 25
#define LIN_RX 18
#define LIN_TX 19
#define LIN_SLP 21

#include "TJA1020.hpp"


// using UART 2 for LinBus
Lin_Interface LinBus(2);
//HardwareSerial LinBus(2);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LIN_SLP, OUTPUT);
  digitalWrite(LIN_SLP, HIGH);
  //pinMode(LIN_RX, INPUT_PULLUP);
  //pinMode(LIN_TX, OUTPUT);
  //digitalWrite(LIN_TX, HIGH);
  // configure baud rate
  Serial.print("configure Lin-Bus to 19200 Baud\n");
  LinBus.baud = 19200;
  LinBus.pin_rx = LIN_RX;
  LinBus.pin_tx = LIN_TX;
  LinBus.verboseMode = 1;
  delay(1000);
 // LinBus.setSlope(LinBus.LowSlope);
  //LinBus.begin(19200, SERIAL_8N1,LIN_RX,LIN_TX);
}
/*
bool readLinData()
{
  bool chkSumValid = false;//LinBus.readFrame(0x0E);
  if (chkSumValid)
  {
    Serial.print("Got Message");
    for(int i = 0;i < 8;i++){
      //Serial.printf("Lin Byte %d = %d\n", i,LinBus.LinMessage[i]);
      //Serial.print("Got Message");
    }
  }
  //LinBus.setMode(LinBus.Sleep);
}
*/

void loop()
{
   
   
   LinBus.LinMessage[0] = 123;
   LinBus.writeFrameClassic(0x0E,8);

   
  delay(1000);
}

