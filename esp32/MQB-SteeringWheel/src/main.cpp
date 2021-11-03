#include <Arduino.h>

#define LED_BUILTIN 25
#define LIN_RX 16
#define LIN_TX 17
#define LIN_SLP 21


#include <Lin_Interface.hpp>

// using UART 2 for LinBus
Lin_Interface LinBus(2);

// data to be filled by bus request
float Cap_Max = 0.0;
float Cap_Available = 0.0;
uint8_t Cap_Configured = 0;
uint8_t CalibByte = 0x00;
bool CalibrationDone = false;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LIN_SLP, OUTPUT);
  digitalWrite(LIN_SLP, HIGH);
  // configure baud rate
  Serial.print("configure Lin-Bus to 19200 Baud\n");
  LinBus.baud = 19200;
  LinBus.pin_rx = LIN_RX;
  LinBus.pin_tx = LIN_TX;
}

bool readLinData()
{
  bool chkSumValid = LinBus.readFrame(0x0E);
  if (chkSumValid)
  {
    Serial.print("Got Message");
    for(int i = 0;i < 8;i++){
      //Serial.printf("Lin Byte %d = %d\n", i,LinBus.LinMessage[i]);
      //Serial.print("Got Message");
    }
  }
  return chkSumValid;
}

void loop()
{
  readLinData();

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
}

