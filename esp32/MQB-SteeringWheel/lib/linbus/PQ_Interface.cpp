#include <Arduino.h>
#include "PQ_Interface.hpp"


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
  light_data[0] = 0x00;
  light_data[1] = 0xF9;
  light_data[2] = 0xFF;
  light_data[3] = 0xFF;

  // Lin
  LinBus.baud = 19200;
  LinBus.pin_rx = LIN2_RX;
  LinBus.pin_tx = LIN2_TX;
  LinBus.verboseMode = 1;

  // Serial.println("\nPQ init");
}


void PQ_Interface::loop() {

  bool chkSumValid = LinBus.readFrame();
  //Serial.println(chkSumValid);
  /*
  int result = 0;

  while (LinBus.available()) {
    request_time = millis();
    uint8_t c = LinBus.read();
    // if (this->verboseMode == 2) {Serial.println("\nPQ in: "); Serial.println(c, HEX);}
    switch (state) {
      case IDLE:
        if (c == 0x55) {
          // if (this->verboseMode == 2) {Serial.println("\nPQ IDLE 55");}
          request[0] = c;
          request_data_index = 0;
          state = READ_REQUEST;
          result = 1;
        }
        break;
      case READ_REQUEST:
        request_id = c & 0b00111111;
        if (this->verboseMode == 2) {
          Serial.println("\nPQ request ");
          Serial.println(request_id, HEX);
        }
        if (request_id == PQ_BUTTONS_ID) {
          if (LinBus.available()) {
            if (this->verboseMode > 0) {
              Serial.println("\nPQ error: income data after request");
            }
            state = IDLE;
            result = -1;
          } else {
            state = WRITE_RESPONSE;
            buttons_response[0] = 0xF0 | ((buttons_response[0] + 1) % 0x0F);
            if ((this->verboseMode == 1) && (buttons_response[1] != pressed_button)) {
              Serial.println("\nPQ button ");
              Serial.println(buttons_response[1], HEX);
            }
            buttons_response[1] = pressed_button;
            buttons_response[6] = pressed_gear_shifter | 0x30;
            if (this->verboseMode == 2) {
              Serial.println("\nPQ response ");
              Serial.println(request_id, HEX);
              Serial.println(":");
              for (int i = 0; i < 8; i++) {
                Serial.println(" ");
                Serial.println(buttons_response[i], HEX);
              }
            }
            write_response(PQ_BUTTONS_ID, buttons_response, 8);
            state = IDLE;
            result = 1;
          }
        } else if (request_id == PQ_LIGHT_ID) {
          state = READ_DATA;
          result = 1;
        } else {
          while (LinBus.available())
            LinBus.read();
          state = IDLE;
          result = -1;
        }
        break;
      case READ_DATA:
        request[request_data_index++] = c;
        if (request_id == PQ_LIGHT_ID && (request_data_index == 4)) {
          state = READ_CHECKSUM;
        }
        result = 1;
        break;
      case READ_CHECKSUM:
        uint8_t checksum = dataChecksum(request_id, request, request_data_index);
        if (checksum == c) {
          if (this->verboseMode == 2) {
            Serial.println("\nPQ data ");
            Serial.println(request_id, HEX);
            Serial.println(":");
            for (int i = 0; i < request_data_index; i++) {
              Serial.println(" ");
              Serial.println(request[i], HEX);
            }
          }
          if (request_id == PQ_LIGHT_ID) {
            memcpy(light_data, request, 4);
          }
          state = IDLE;
          result = 1;
        } else {
          if (this->verboseMode > 0) {
            Serial.println("\nPQ checksum mismatch ");
            Serial.println(request_id, HEX);
            Serial.println(": ");
            for (int i = 0; i < request_data_index; i++) {
              Serial.println(" ");
              Serial.println(request[i], HEX);
            }
            Serial.println(" => ");
            Serial.println(checksum, HEX);
            Serial.println("vs ");
            Serial.println(c, HEX);
          }
          state = IDLE;
          result = -1;
        }
        break;
    }
  }
  */
  //return result;
}

/*
int PQ_Interface::write_response(uint8_t ident, uint8_t data[], uint8_t data_size) {
  uint8_t cksum = dataChecksum(ident, data, data_size);
  for (uint8_t i = 0; i < data_size; i++) {
    LinBus.write(data[i]);
  }
  LinBus.write(cksum);
  return 1;
}

#define BIT(data, shift) ((addr & (1 << shift)) >> shift)
uint8_t addrParity(uint8_t addr) {
  uint8_t p0 = BIT(addr, 0) ^ BIT(addr, 1) ^ BIT(addr, 2) ^ BIT(addr, 4);
  uint8_t p1 = ~(BIT(addr, 1) ^ BIT(addr, 3) ^ BIT(addr, 4) ^ BIT(addr, 5));
  return (p0 | (p1 << 1)) << 6;
}

uint8_t dataChecksum(uint8_t id, const uint8_t* message, uint8_t nBytes) {
  uint16_t sum = id | addrParity(id);
  while (nBytes-- > 0)
    sum += *(message++);
  // Add the carry
  while (sum >> 8)  // In case adding the carry causes another carry
    sum = (sum & 255) + (sum >> 8);
  return (~sum);
}
*/