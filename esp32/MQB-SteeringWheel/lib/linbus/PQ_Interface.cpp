#include <Arduino.h>
#include "PQ_Interface.h"


void PQ_Interface::setup() {
  // Button Data:
  buttons_response[0] = 0xFF;
  buttons_response[1] = 0x00;
  buttons_response[2] = 0xFF;
  buttons_response[3] = 0xF0;
  buttons_response[4] = 0x60;
  buttons_response[5] = 0x00;
  buttons_response[6] = 0x30;
  buttons_response[7] = 0x00;
  // Light Data:
  light_data[0] = 0x76;
  light_data[1] = 0x00;
  light_data[2] = 0xEF;
  light_data[3] = 0xFC;

  // Lin
  LinBus.baud = 19200;
  LinBus.pin_rx = LIN1_RX;
  LinBus.pin_tx = LIN1_TX;
  LinBus.verboseMode = 0;

  // Serial.println("\nPQ init");
}

void PQ_Interface::loop() {
  // Serial.println(LinBus.pin_rx);
  // Serial.println(LinBus.pin_tx);
  LinBus.begin(LinBus.baud, SERIAL_8N1, LinBus.pin_rx, LinBus.pin_tx);

  while (1) {
    int protectedId = 0;
    // switch()
    if (LinBus.available()) {
      int startTime = millis();
      int currentPosition = 0;

      byte buffer[255];

      byte currentData;
      // Read until timeout(Idea from https://github.com/skpang/Teensy32_LIN-bus_slave_demo/blob/master/lin-bus.cpp)
      while ((millis() - startTime) <= 7) {
        if (LinBus.available()) {
          currentData = LinBus.read();
          currentPosition++;
          switch (currentPosition) {
            case 1:
              if (currentData != 0) {
                if (LinBus.verboseMode == 1) {
                  Serial.println("Discarding Frame, because of invalid header(0)");
                  // Serial.println(currentData);
                }
                currentPosition = 0;
              }
              break;
            case 2:
              if (currentData != 0x55) {
                if (LinBus.verboseMode == 1) {
                  Serial.println("Discarding Frame, because of invalid header(0x55)");
                  // Serial.println(currentData);
                }
                currentPosition = 0;
              }
              break;
            case 3:
              protectedId = currentData;
              processRequest(protectedId);
              break;
            default:
              // buffer[currentPosition] = currentBuffer;
              break;
          }
        }
      }

      /*
          if (currentPosition != 3) {
            // Its a request + response
            for (int i = 0; i < currentPosition; i++) {
              Serial.printf("%02X ", buffer[i]);
            }
            Serial.println("");
          }
          */
    }
  }
}

/// @brief Checksum calculation for LIN Frame
/// @details
/// EnhancedChecksum considers ProtectedID
///     LIN 2.0 only for FrameID between 0x00..0x3B
///     LIN 2.0 uses for 0x3C and above ClassicChecksum for legacy (auto detected)
/// ClassicChecksum
///     LIN 1.x in general (use 'ProtectedID' = 0x00 to ensure that)
/// see LIN Specification 2.2A (2021-12-31) for details
///     https://microchipdeveloper.com/local--files/lin:specification/LIN-Spec_2.2_Rev_A.PDF
///     2.8.3 Example of Checksum Calculation
/// @param ProtectedID initial Byte, set to 0x00, when calc Checksum for classic LIN Frame
/// @param dataLen length of Frame (only Data Bytes)
/// @returns calculated checksum
uint8_t PQ_Interface::getChecksum(uint8_t ProtectedID, uint8_t* data, uint8_t dataLen) {
  uint16_t sum = ProtectedID;
  // test FrameID bits for classicChecksum
  if ((sum & 0x3F) >= 0x3C) {
    // LIN 1.x: legacy
    // LIN 2.0: don't include PID for ChkSum calculation on configuration and reserved frames
    sum = 0x00;
  }
  // sum up all bytes (including carryover to the high byte)
  // ID allready considered
  while (dataLen-- > 0)
    sum += data[dataLen];
  // add high byte (carry over) to the low byte
  while (sum >> 8)
    sum = (sum & 0xFF) + (sum >> 8);
  // inverting result
  return (~sum);
}

// Response Handler:
void PQ_Interface::processRequest(uint8_t protectedId) {
  if (protectedId == 0xF0) {
    // writeResponse(protectedId, buttons_response, 8);
  }
  if (protectedId == 0x61) {
    // writeResponse(protectedId, light_data, 4);
  }
  //debugService.addLinMessage(protectedId, 0, 0);
}
// Writes a response back to PQ
void PQ_Interface::writeResponse(uint8_t protectedId, uint8_t* data, uint8_t dataLen) {
  // Serial.printf("%02X ", protectedId);
  // Serial.println();
  byte protectedId2 = protectedId & 0b00111111;

  // Serial.printf("%02X ", protectedId2);
  // Serial.println();
  return;
  // data[2] = random(100, 255);
  for (int i = 0; i < dataLen; ++i) {
    // data[i] = random(0, 255);
    // data[i] = random(0, 255);
    // Serial.printf("%02X ", data[i]);
  }
  // Serial.println();

  uint8_t cksum = getChecksum(0x00, data, dataLen);
  for (int i = 0; i < dataLen; ++i) {
    LinBus.write(data[i]);  // Message (array from 1..8)
  }
  LinBus.write(cksum);
  LinBus.flush();
}
