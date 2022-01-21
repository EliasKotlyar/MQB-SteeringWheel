#include <ESP8266React.h>
#include <LightStateService.h>
#include <MQBService.h>
#include <MQB_Interface.hpp>
#include <ShiftRegService.h>
MQB_Interface mqb;
#define SERIAL_BAUD_RATE 115200
#define LIN_SLP 13

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
LightStateService lightStateService = LightStateService(&server, esp8266React.getSecurityManager());
MQBService mqbStateService = MQBService(&server, esp8266React.getSecurityManager());
ShiftRegService shiftRegService = ShiftRegService(&server, esp8266React.getSecurityManager());


void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  mqb.setup();

  pinMode(LIN_SLP, OUTPUT);
  digitalWrite(LIN_SLP, HIGH);


  // start the framework and demo project
  esp8266React.begin();

  // load the initial light settings
  mqbStateService.begin();
  shiftRegService.begin();


  // start the server
  server.begin();
}

void loop() {
  // run the framework's loop function
  esp8266React.loop();
  mqb.loop();
  if(mqb.hasKeysPressed()){
    byte key = mqb.getLastKey();
    String keyStr = MQB_Interface::getKeyName(key);
    Serial.println("Key Pressed " + keyStr);    
    mqbStateService.update([&](MQBState& state) {
      if (state.lastKeyPressed == key) {
        return StateUpdateResult::UNCHANGED; // lights were already on, return UNCHANGED
      }
      state.lastKeyPressed = key;  // turn on the lights
      return StateUpdateResult::CHANGED; // notify StatefulService by returning CHANGED
    }, "timer");

    //digitalWrite(LED_RED, LOW);   // turn the LED on (HIGH is the voltage level)
    //delay(1000);                       // wait for a second
    //digitalWrite(LED_RED, HIGH);    // turn the LED off by making the voltage LOW
  }
}
