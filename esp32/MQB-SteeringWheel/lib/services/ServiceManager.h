// MQB_Interface.h
//
// Provides a Interface to MQB Steering Wheel

#include <ESP8266React.h>
#include <LightStateService.h>
#include <MQBService.h>
#include <MQB_Interface.hpp>
#include <ShiftRegService.h>
#include <PQ_Interface.hpp>
#include <DebugService.h>
#include <ConfigService.h>
#include <TempService.h>
#define SERIAL_BAUD_RATE 115200
#define LIN_SLP 13
class ServiceManager {
 public:
  void startServices();

 private:
  MQB_Interface mqb;
  PQ_Interface pq;
};
