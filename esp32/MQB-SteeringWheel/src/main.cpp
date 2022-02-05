#include <ESP8266React.h>
#include <LightStateService.h>
#include <MQBService.h>
#include <MQB_Interface.hpp>
#include <ShiftRegService.h>
#include <PQ_Interface.hpp>
#include <DebugService.h>
MQB_Interface mqb;
//PQ_Interface pq;
#define SERIAL_BAUD_RATE 115200
#define LIN_SLP 13

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
LightStateService lightStateService = LightStateService(&server, esp8266React.getSecurityManager());
MQBService mqbStateService = MQBService(&server, esp8266React.getSecurityManager());
ShiftRegService shiftRegService = ShiftRegService(&server, esp8266React.getSecurityManager());
DebugService debugService = DebugService(&server, esp8266React.getSecurityManager());



void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  mqb.setup();

  pinMode(LIN_SLP, OUTPUT);
  digitalWrite(LIN_SLP, HIGH);


  // start the framework and demo project
  esp8266React.begin();

  // Load all the services:
  mqbStateService.begin();
  shiftRegService.begin();
  debugService.begin();

  // start the server
  server.begin();


  // Setup the PQ and MQB Interfaces:
  //pq.setup();
  //mqb.setup();
  randomSeed(0);
}

void loop() {
  // run the framework's loop function
  esp8266React.loop();
  mqb.loop();
  //pq.loop();
  
  
  if(mqb.hasKeysPressed()){
    byte key = mqb.getLastKey();
    int temp = mqb.getTemp();
    String keyStr = MQB_Interface::getKeyName(key);
    Serial.println("Key Pressed " + keyStr);    
    mqbStateService.update([&](MQBState& state) {
      if (state.lastKeyPressed == key && state.temp == temp ) {
        return StateUpdateResult::UNCHANGED; // lights were already on, return UNCHANGED
      }
      state.lastKeyPressed = key;  // turn on the lights
      state.temp = temp;
      return StateUpdateResult::CHANGED; // notify StatefulService by returning CHANGED
    }, "timer");

  }
  
}
