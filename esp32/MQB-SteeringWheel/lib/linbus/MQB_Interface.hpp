// MQB_Interface.h
//
// Provides a Interface to MQB Steering Wheel

#pragma once
#ifndef MQB_Interface_h
#define MQB_Interface_h

#include "Lin_Interface.hpp"
#include <Arduino.h>
#include <map>

class MQB_Interface {
 public:
  MQB_Interface() : LinBus(2) {
  }
  void setup();
  void loop();
  void getLastKeyCode();

  uint8_t getTemp();

  String getLastKey();
  bool hasKeysPressed();

 protected:
  Lin_Interface LinBus;
  void readLinData(uint8_t frameId);
  String lastKeyPressed;
  void dumpBuffer();
  uint8_t lightValue = 255;
  uint8_t temp = 0;
  void checkLastKey(byte linKey);

  std::map<String, byte> mqbKeyArray = {
      {"MQB_NONE", 0x00},
      {"MQB_RESET", 0x88},
      {"MQB_PLUS", 0x82},
      {"MQB_ACC", 0xB0},
      {"MQB_MINUS", 0x84},
      {"MQB_SET", 0x81},
      {"MQB_SHAKE", 0x0C},
      {"MQB_VOL_PLUS", 0x10},
      {"MQB_VOL_MINUS", 0x11},
      // Right Side:
      {"MQB_SPEAK", 0x19},
      {"MQB_UP", 0x04},
      {"MQB_LEFT", 0x03},
      {"MQB_OK", 0x07},
      {"MQB_RIGHT", 0x02},
      {"MQB_VIEW", 0x23},
      {"MQB_DOWN", 0x05},
      {"MQB_FORWARD", 0x16},
      {"MQB_REVERSE", 0x15},
  };
};
#endif
