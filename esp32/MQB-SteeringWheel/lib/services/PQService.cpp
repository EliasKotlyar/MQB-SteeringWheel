#include <PQService.h>

PQService::PQService(AsyncWebServer* server,
                     SecurityManager* securityManager,
                     Lin_Interface* lin,
                     DebugService* debugService) :

    _httpEndpoint(PQState::read,
                  PQState::update,
                  this,
                  server,
                  "/rest/PQState",
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(PQState::read,
               PQState::update,
               this,
               server,
               "/ws/PQState",
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  LinBus = lin;
  this->debugService = debugService;
}

void PQService::begin() {
  _state.lastKeyPressed = "PQ_NONE";
  xTaskCreate(this->startTaskImpl, "PQTASK", 2048, this, 5, NULL);

  LinBus->startSerial();
}

void PQService::setKey(String key) {
  this->update(
      [&](PQState& state) {
        if (state.lastKeyPressed == key) {
          return StateUpdateResult::UNCHANGED;
        }
        if (key != "PQ_NONE") {
          Serial.println("Key Pressed " + key);
        }
        state.lastKeyPressed = key;
        return StateUpdateResult::CHANGED;
      },
      "setkeymethod");
}

void PQService::startTaskImpl(void* _this) {
  static_cast<PQService*>(_this)->loop();
}

void PQService::loop(void) {
  const TickType_t xDelay = 100 / portTICK_PERIOD_MS;

  while (1) {
    byte protectedID = LinBus->readLinHeader();
    if (protectedID != 0) {
      this->processData(protectedID);
      Serial.print("Protected ID: ");
      Serial.printf("%02X ", protectedID);
      Serial.print("  ");
      LinBus->dumpBuffer();
      Serial.println();
      this->debugService->addLinMessage(protectedID, LinBus->LinMessage, LinBus->bytes_received);
    }
    vTaskDelay(xDelay);
  }
}

void PQService::processData(byte protectedId) {
  switch (protectedId) {
    case BUTTONS_ID:

      // Button Data:
      byte keyid = this->getKeyIDByName("PQ_PREV");
      buttons_response[0] = 0xF0 | ((buttons_response[0] + 1) % 0x0F);
      if (keyid != 0) {
        buttons_response[1] = keyid;
      }

      LinBus->writeResponse(protectedId, buttons_response, 8);

      /*
      for (uint8_t i = 0; i < 8; i++) {
        Serial.printf("%02X ", buttons_response[i]);
      }
      Serial.println();
      */

      // LinBus->dumpBuffer();

      break;
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
byte PQService::getKeyIDByName(String name) {
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
