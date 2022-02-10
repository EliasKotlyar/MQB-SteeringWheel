#include <ServiceManager.h>

void ServiceManager::startServices() {
  AsyncWebServer server(80);
  ESP8266React esp8266React(&server);
  LightStateService lightStateService = LightStateService(&server, esp8266React.getSecurityManager());
  MQBService mqbStateService = MQBService(&server, esp8266React.getSecurityManager());
  ShiftRegService shiftRegService = ShiftRegService(&server, esp8266React.getSecurityManager());
  DebugService debugService = DebugService(&server, esp8266React.getSecurityManager());
  TempService tempService = TempService(&server, esp8266React.getSecurityManager());
  ConfigService configService = ConfigService(&server, esp8266React.getSecurityManager(), esp8266React.getFS());
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

  // Setup the PQ and MQB Interfaces:
  pq.setup();
  mqb.setup();
  // mqb.setup();

  pinMode(LIN_SLP, OUTPUT);
  digitalWrite(LIN_SLP, HIGH);

  randomSeed(0);
}
