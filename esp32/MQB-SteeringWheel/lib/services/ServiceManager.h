// MQB_Interface.h
//
// Provides a Interface to MQB Steering Wheel

#include <ESP8266React.h>
#include <LightStateService.h>
#include <MQBService.h>
#include <Lin_Interface.h>
#include <ShiftRegService.h>
#include <PQSlave.h>
#include <PQMaster.h>
#include <DebugService.h>
#include <ConfigService.h>
#include <TempService.h>
#define SERIAL_BAUD_RATE 115200
#define LIN_SLP 13
class ServiceManager {
 public:
  void loop();
  void setup();
  DebugService* getDebugService();
  Lin_Interface* getLin1();

 private:
  Lin_Interface Lin1 = Lin_Interface(1);
  Lin_Interface Lin2 = Lin_Interface(2);

  // All Services:
  AsyncWebServer server = AsyncWebServer(80);
  ESP8266React esp8266React = ESP8266React(&server);
  LightStateService lightStateService = LightStateService(&server, esp8266React.getSecurityManager());

  ShiftRegService shiftRegService = ShiftRegService(&server, esp8266React.getSecurityManager());
  DebugService debugService = DebugService(&server, esp8266React.getSecurityManager());
  TempService tempService = TempService(&server, esp8266React.getSecurityManager());
  ConfigService configService = ConfigService(&server, esp8266React.getSecurityManager(), esp8266React.getFS());

  // Service:
  MQBService mqbStateService = MQBService(&server, esp8266React.getSecurityManager(), &Lin2);
  PQSlave pqStateService = PQSlave(&server, esp8266React.getSecurityManager(), &Lin1, &debugService);
  PQMasterService pqmaster = PQMasterService(&server, esp8266React.getSecurityManager(), &Lin2);
};
