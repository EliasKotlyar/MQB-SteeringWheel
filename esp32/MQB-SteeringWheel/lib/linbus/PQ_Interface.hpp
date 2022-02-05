// PQ_Interface.h
//
// Provides a Interface to PQ Steering Wheel

#pragma once
#include "Lin_Interface.hpp"
#include <Arduino.h>




#define IDNAME(name) #name

#define PQ_BUTTONS_ID 0x0E
#define PQ_LIGHT_ID 0x0D

enum PQKeys {
  PQ_Prev,
  PQ_Next,
  PQ_PhoneVoiceMic,
  PQ_Phone,
  PQ_View,
  PQ_Up,
  PQ_Down,
  PQ_SrcMinus,
  PQ_SrcPlus,
  PQ_OK,
  PQ_VOL_PLUS,
  PQ_VOL_MINUS,
  PQ_ACC,
  // No Key pressed:
  PQ_NONE
};
const uint8_t PQKeyCodes[] = {
    0x16,  // prev
    0x15,  // next
    0x19,  // phone <- voice/mic
    0x1C,  // phone
    0x23,  // return <- view (on wheels with "view" button)
    0x04,  // up
    0x05,  // down
    0x03,  // src-
    0x02,  // src+
    0x07,  // ok
    0x10,  // vol+
    0x11,  // vol-
    0x0C,  // voice/mic <- ACC mode (on wheels with "view" button)
    0x00,  // None
};

const char static* PQKeyNames[] = {

    // No Key pressed:
    IDNAME(PQ_Prev),
    IDNAME(PQ_Next),
    IDNAME(PQ_PhoneVoiceMic),
    IDNAME(PQ_Phone),
    IDNAME(PQ_View),
    IDNAME(PQ_Up),
    IDNAME(PQ_Down),
    IDNAME(PQ_SrcMinus),
    IDNAME(PQ_SrcPlus),
    IDNAME(PQ_OK),
    IDNAME(PQ_VOL_PLUS),
    IDNAME(PQ_VOL_MINUS),
    IDNAME(PQ_ACC),
    IDNAME(PQ_NONE),

};

class PQ_Interface {
 public:
  PQ_Interface() : LinBus(1){

  };
  void setup();
  void loop();
  uint8_t getTemp();

 protected:
  void readLinData(uint8_t frameId);
  PQKeys lastKeyPressed;
  void dumpBuffer();
  uint8_t lightValue = 255;
  uint8_t temp = 0;

  uint8_t pressed_button = 0;
  uint8_t pressed_gear_shifter = 0;
  uint8_t light_data[4];

  Lin_Interface LinBus;
  bool verboseMode = true;

  int write_response(uint8_t ident, uint8_t data[], uint8_t data_size);

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
};
