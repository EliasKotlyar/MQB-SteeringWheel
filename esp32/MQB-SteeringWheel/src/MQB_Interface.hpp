// MQB_Interface.h
//
// Provides a Interface to MQB Steering Wheel

#pragma once
#include "Lin_Interface.hpp"
#include <Arduino.h>
#define LIN_RX 18
#define LIN_TX 19
#define IDNAME(name) #name

enum MQBKeys
{
    // From Top to bottom and left to right:
    MQB_RESET,
    MQB_PLUS,
    MQB_ACC,
    MQB_MINUS,
    MQB_SET,
    MQB_SHAKE,
    MQB_VOL_PLUS,
    MQB_VOL_MINUS,
    // Right Side:
    MQB_SPEAK,
    MQB_UP,
    MQB_LEFT,
    MQB_OK,
    MQB_RIGHT,
    MQB_VIEW,
    MQB_DOWN,
    MQB_FORWARD,
    MQB_REVERSE,
    // Special Keys:
    MQB_HORN,
    MQB_ONOFF,
    // No Key pressed:
    MQB_NONE
};
const uint8_t MQBKeyCodes[] = {
    0x88, //MQB_RESET
    0x82, //MQB_PLUS,
    0xB0, //MQB_ACC,
    0x84, //MQB_MINUS,
    0x81, //MQB_SET,
    0x0C, //MQB_SHAKE,
    0x10, //MQB_VOL_PLUS,
    0x11, //MQB_VOL_MINUS,
    // Right Side:
    0x19, //MQB_SPEAK,
    0x04, //MQB_UP,
    0x03, //MQB_LEFT,
    0x07, //MQB_OK,
    0x02, //MQB_RIGHT,
    0x23, //MQB_VIEW,
    0x05, //MQB_DOWN,
    0x16, //MQB_FORWARD,
    0x15, //MQB_REVERSE
};

const char static *MQBKeyNames[] = {
    IDNAME(MQB_RESET),
    IDNAME(MQB_PLUS),
    IDNAME(MQB_ACC),
    IDNAME(MQB_MINUS),
    IDNAME(MQB_SET),
    IDNAME(MQB_SHAKE),
    IDNAME(MQB_VOL_PLUS),
    IDNAME(MQB_VOL_MINUS),
    // Right Side:
    IDNAME(MQB_SPEAK),
    IDNAME(MQB_UP),
    IDNAME(MQB_LEFT),
    IDNAME(MQB_OK),
    IDNAME(MQB_RIGHT),
    IDNAME(MQB_VIEW),
    IDNAME(MQB_DOWN),
    IDNAME(MQB_FORWARD),
    IDNAME(MQB_REVERSE),
    IDNAME(MQB_HORN),    
    IDNAME(MQB_ONOFF),

};

class MQB_Interface
{
public:
    MQB_Interface() : LinBus(2) {}
    void setup();
    void loop();
    void getLastKeyCode();
    String getLastKeyString();
    bool hasKeysPressed();
    

protected:
    Lin_Interface LinBus;
    void readLinData(uint8_t frameId);
    MQBKeys lastKeyPressed;
    void dumpBuffer();
    uint8_t lightValue = 255;
};
