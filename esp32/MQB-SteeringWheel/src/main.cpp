#include <ESP8266React.h>
#include <LightStateService.h>
#include <MQBService.h>
#include <MQB_Interface.hpp>
#include <ShiftRegService.h>
#include <PQ_Interface.hpp>
#include <DebugService.h>
MQB_Interface mqb;
PQ_Interface pq;
#define SERIAL_BAUD_RATE 115200
#define LIN_SLP 13

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
LightStateService lightStateService = LightStateService(&server, esp8266React.getSecurityManager());
MQBService mqbStateService = MQBService(&server, esp8266React.getSecurityManager());
ShiftRegService shiftRegService = ShiftRegService(&server, esp8266React.getSecurityManager());
DebugService debugService = DebugService(&server, esp8266React.getSecurityManager());


void pqLoop(void* parameter) {
  pq.loop();
}

void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // mqb.setup();

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
  pq.setup();
  mqb.setup();
  randomSeed(0);
  xTaskCreate(pqLoop,        // Function that should be called
              "Toggle LED",  // Name of the task (for debugging)
              1000,          // Stack size (bytes)
              NULL,          // Parameter to pass
              1,             // Task priority
              NULL           // Task handle
  );
}


void loop() {
  // run the framework's loop function
  esp8266React.loop();
  mqb.loop();


  String key = mqb.getLastKey();
  byte keyNumber = 0;
  if (key == "MQB_MINUS") {
    keyNumber = 6;
  }
  if (key == "MQB_PLUS") {
    keyNumber = 7;
  }
  shiftRegService.setNumber(keyNumber);
  mqbStateService.setKey(key);
}
