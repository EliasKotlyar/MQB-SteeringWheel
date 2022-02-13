#include <PQMaster.h>

PQMasterService::PQMasterService(AsyncWebServer* server, SecurityManager* securityManager, Lin_Interface* lin) :

    _httpEndpoint(PQMasterState::read,
                  PQMasterState::update,
                  this,
                  server,
                  "/rest/PQMasterState",
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(PQMasterState::read,
               PQMasterState::update,
               this,
               server,
               "/ws/PQMasterState",
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  LinBus = lin;
}

void PQMasterService::begin() {
  _state.lastKeyPressed = "PQMaster_NONE";
}

void PQMasterService::setKey(String key) {
  this->update(
      [&](PQMasterState& state) {
        if (state.lastKeyPressed == key) {
          return StateUpdateResult::UNCHANGED;
        }
        if (key != "PQMaster_NONE") {
          Serial.println("Key Pressed " + key);
        }
        state.lastKeyPressed = key;
        return StateUpdateResult::CHANGED;
      },
      "setkeymethod");
}

void PQMasterService::loop(void) {
  lastKeyPressed = "PQMaster_NONE";
  // Request Data:
  readLinData(0x0E);
  

  // Light Message:
  LinBus->LinMessage[0] = 0x76;
  LinBus->LinMessage[1] = 0x00;  
  LinBus->LinMessage[2] = 0xEF;
  LinBus->LinMessage[3] = 0xFC;
  LinBus->writeFrame(0x0D, 4);


  //this->setKey(lastKeyPressed);
}

void PQMasterService::checkLastKey(byte linKey) {
  for (std::map<String, byte>::iterator it = PQMasterKeyArray.begin(); it != PQMasterKeyArray.end(); ++it) {
    String name = it->first;
    byte keyId = it->second;
    if (keyId == linKey) {
      lastKeyPressed = name;
    }
  }
}

void PQMasterService::readLinData(uint8_t frameId) {
  bool chkSumValid = LinBus->readFrame(frameId);
  if (chkSumValid) {
    //LinBus->dumpBuffer();
    //Serial.println();
  }
}
