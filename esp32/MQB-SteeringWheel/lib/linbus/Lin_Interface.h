// Lin_Interface.h
//
// Provides a Hardware LIN Interface
// inherited from the "HardwareSerial"
//
// * Frame sending [Break, Sync, PID, Data, Checksum]
// * Frame request [Break, Sync, PID] and wait for data from slave + verify checksum
//
// * WriteBreak for initiation of a Lin-Frame
// * Convert FID to PID
// * Calculation of Checksum (to be send, or to be verified)

#pragma once

#include <Arduino.h>

#define LIN1_TX 32
#define LIN1_RX 33

#define LIN2_TX 25
#define LIN2_RX 26

#pragma once

#include <Arduino.h>

class Lin_Interface : public HardwareSerial {
 public:
  // inherit constructor from HardwareSerial (Parameter: int uart_nr)
  Lin_Interface(int uart_nr) : HardwareSerial(uart_nr) {
        if (uart_nr == 1) {
      pin_rx = LIN1_RX;
      pin_tx = LIN1_RX;
    } else {
      pin_rx = LIN2_RX;
      pin_tx = LIN2_RX;
    }
  }

  int verboseMode = -1;
  unsigned long baud = 19200;
  int8_t pin_rx = 0;
  int8_t pin_tx = 0;

  // 8 Data Bytes + ChkSum + some space for receiving complete frames
  uint8_t LinMessage[8 + 1 + 4] = {0};

  bool readFrame(uint8_t FrameID);

  void writeFrame(uint8_t FrameID, uint8_t datalen);
  void writeFrameClassic(uint8_t FrameID, uint8_t datalen);
  void dumpBuffer();

 protected:
  uint32_t m_bitCycles;
  size_t writeBreak();
  uint8_t getProtectedID(uint8_t FrameID);
  uint8_t getChecksum(uint8_t ProtectedID, uint8_t datalen);
  
};