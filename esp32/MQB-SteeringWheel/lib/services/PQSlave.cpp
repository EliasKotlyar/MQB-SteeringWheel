#include <PQSlave.h>

PQSlave::PQSlave(AsyncWebServer* server,
                 SecurityManager* securityManager,
                 Lin_Interface* lin,
                 DebugService* debugService) :

    _httpEndpoint(PQSlaveState::read,
                  PQSlaveState::update,
                  this,
                  server,
                  "/rest/PQSlaveState",
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(PQSlaveState::read,
               PQSlaveState::update,
               this,
               server,
               "/ws/PQSlaveState",
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  LinBus = lin;
  this->debugService = debugService;
}

void PQSlave::begin() {
  TaskHandle_t Core0TaskHnd;
  _state.keyPressed = "PQ_NONE";
  // xTaskCreate(this->startTaskImpl, "PQTASK", 2048, this, 5, NULL );
  // Pin to Core 1, instead of 0 //
  // https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/esp32-nutzung-beider-cpu-kerne-fuer-eigene-projekte
  byte coreid = 0;
  xTaskCreatePinnedToCore(this->startTaskImpl, "PQTASK", 2048, this, 5, &Core0TaskHnd, coreid);
}

void PQSlave::setKey(String key) {
  this->update(
      [&](PQSlaveState& state) {
        if (state.keyPressed == key) {
          return StateUpdateResult::UNCHANGED;
        }
        if (key != "PQ_NONE") {
          Serial.println("PQ Key Pressed " + key);
        }
        state.keyPressed = key;
        return StateUpdateResult::CHANGED;
      },
      "setkeymethod");
}

void PQSlave::startTaskImpl(void* _this) {
  static_cast<PQSlave*>(_this)->loop();
}

void PQSlave::loop(void) {
  Serial.print("PQ Task is on core:");
  Serial.println(xPortGetCoreID());
  LinBus->startSerial();
  while (1) {
    byte protectedID = LinBus->readLinHeader();
    if (protectedID != 0) {
      this->processData(protectedID);
      // this->debugService->addLinMessage(protectedID, LinBus->LinMessage, LinBus->bytes_received);
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);
    // rtc_wdt_feed();
  }
}

void PQSlave::processData(byte protectedId) {
  switch (protectedId) {
    case BUTTONS_ID: {
      // Serial.print("Protected ID: ");
      // Serial.printf("%02X ", protectedId);
      // Serial.print("  ");
      //  Button Data:

      buttons_response[0] = 0xF0 | ((buttons_response[0] + 1) % 0x10);
      buttons_response[6] = 0 | 0x30;
      buttons_response[7] = 0;

      byte keyid = this->getKeyIDByName(_state.keyPressed);
      if (keyid != 0) {
        // Serial.println(keyid);
      }
      buttons_response[1] = keyid;
      if (_state.keyPressed == "PQ_HORN") {
        buttons_response[7] = 0x02;
      }
      /*
       */
      // buttons_response[1] = 0x07;

      /*
      if (buttons_response[1] == 0x07) {
        buttons_response[1] = 0;
      } else {
        buttons_response[1] = 0x07;
      }
      */
      /*
      for (uint8_t i = 0; i < 8; i++) {
        Serial.printf("%02X ", buttons_response[i]);
      }
      Serial.println();
      */

      // vTaskDelay(1 / portTICK_PERIOD_MS);
      LinBus->writeResponse(protectedId, buttons_response, 8);

      /*
      for (uint8_t i = 0; i < 8; i++) {
        Serial.printf("%02X ", buttons_response[i]);
      }
      Serial.println();
      */
      // LinBus->dumpBuffer();
      break;
    }
    case LIGHT_ID: {
      // Serial.println(protectedId);
      // Read 5 Bytes:
      for (uint8_t i = 0; i < 5; i++) {
        LinBus->read();
      }
      break;
    }
    default: {
      break;
    }

      /*case LIGHT_ID:
        // Do Nothing...Probably it can read something like that:
  uint8_t light_data[8];
  // Light Data:
  light_data[0] = 0x76;
  light_data[1] = 0x00;
  light_data[2] = 0xEF;
  light_data[3] = 0xFC;
          //break;
        */
  }
}
byte PQSlave::getKeyIDByName(String name) {
  byte retId = 0;
  for (std::map<String, byte>::iterator it = PQKeyArray.begin(); it != PQKeyArray.end(); ++it) {
    String keyName = it->first;
    byte keyId = it->second;
    if (name == keyName) {
      retId = keyId;
      break;
    }
  }
  return retId;
}
