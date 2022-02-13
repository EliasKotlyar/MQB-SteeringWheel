#include <ServiceManager.h>

void ServiceManager::setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // start the framework and demo project
  esp8266React.begin();
  // Load all the services:

  shiftRegService.begin();
  debugService.begin();
  
  tempService.begin();
  mqbStateService.begin();  
  //pqmaster.begin();

  configService.begin();
  // start the server
  server.begin();

  pinMode(LIN_SLP, OUTPUT);
  digitalWrite(LIN_SLP, HIGH);

  pqStateService.begin();


  randomSeed(0);
}

void ServiceManager::loop() {
  esp8266React.loop();
  mqbStateService.loop();

}


