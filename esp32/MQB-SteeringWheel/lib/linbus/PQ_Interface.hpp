// PQ_Interface.h
//
// Provides a Interface to PQ Steering Wheel

#pragma once
#include "Lin_Interface.hpp"
#include <Arduino.h>
#include <map>
#define IDNAME(name) #name

#define PQ_BUTTONS_ID 0x0E
#define PQ_LIGHT_ID 0x0D

class PQ_Interface {
 public:
  PQ_Interface() :
      LinBus(1){

      };
  void setup();
  void loop();
  uint8_t getTemp();

 protected:
  void readLinData(uint8_t frameId);
  String lastKeyPressed;
  void dumpBuffer();
  uint8_t lightValue = 255;
  uint8_t temp = 0;

  uint8_t pressed_button = 0;
  uint8_t pressed_gear_shifter = 0;
  uint8_t light_data[4];

  Lin_Interface LinBus;
  bool verboseMode = true;

  void processRequest(uint8_t protectedId);
  uint8_t getChecksum(uint8_t ProtectedID, uint8_t* data, uint8_t dataLen);
  void writeResponse(uint8_t protectedId, uint8_t* data, uint8_t datalen);

 private:
  enum {
    IDLE,
    READ_REQUEST,
    READ_DATA,
    READ_CHECKSUM,
    WRITE_RESPONSE,
  } state;

  uint8_t request_id = 0;
  uint8_t request[4];
  uint8_t request_data_index = 0;
  uint8_t buttons_response[8];
  unsigned long request_time = 0;

  std::map<String, byte> pqKeyArray = {

      {"PQ_PREV", 0x16},
      {"PQ_Next", 0x15},
      {"PQ_PhoneVoiceMic", 0x19},
      {"PQ_Phone", 0x1C},
      {"PQ_View", 0x23},
      {"PQ_Up", 0x04},
      {"PQ_Down", 0x05},
      {"PQ_SrcMinus", 0x02},
      {"PQ_SrcPlus", 0x07},


  };
};
