#include <ServiceManager.h>

void ServiceManager::setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // start the framework and demo project
  esp8266React.begin();
  // Load all the services:
  mqbStateService.begin();
  shiftRegService.begin();
  debugService.begin();
  configService.begin();
  tempService.begin();

  // start the server
  server.begin();

  // mqb.setup();

  pinMode(LIN_SLP, OUTPUT);
  digitalWrite(LIN_SLP, HIGH);

  randomSeed(0);
}

void ServiceManager::loop() {
  esp8266React.loop();
  mqbStateService.loop();

  // String key = mqb.getLastKey();
  /*
  byte keyNumber = 0;
  if (key == "MQB_MINUS") {
    keyNumber = 6;
  }
  if (key == "MQB_PLUS") {
    keyNumber = 7;
  }
  shiftRegService.setNumber(keyNumber);
  */
  // mqbStateService.setKey(key);
}