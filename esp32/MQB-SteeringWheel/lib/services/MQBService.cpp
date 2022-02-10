#include <MQBService.h>

MQBService::MQBService(AsyncWebServer* server, SecurityManager* securityManager, Lin_Interface* lin) :

    _httpEndpoint(MQBState::read,
                  MQBState::update,
                  this,
                  server,
                  "/rest/MQBState",
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(MQBState::read,
               MQBState::update,
               this,
               server,
               "/ws/MQBState",
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  LinBus = lin;
}

void MQBService::begin() {
  _state.lastKeyPressed = "MQB_NONE";
}

void MQBService::setKey(String key) {
  this->update(
      [&](MQBState& state) {
        if (state.lastKeyPressed == key) {
          return StateUpdateResult::UNCHANGED;
        }
        if (key != "MQB_NONE") {
          Serial.println("Key Pressed " + key);
        }
        state.lastKeyPressed = key;
        return StateUpdateResult::CHANGED;
      },
      "setkeymethod");
}

void MQBService::loop(void) {
  lastKeyPressed = "MQB_NONE";
  readLinData(0x0E);
  readLinData(0x0F);
  readLinData(0x3A);

  // See : https://petrosprojects.blogspot.com/?view=sidebar
  // Send Lin Data:
  // 0x00 = Light off
  // 0x06 = Light with Engine on
  // 0x06 to 0x5C = Backlight dimming
  LinBus->LinMessage[0] = lightValue;
  // FF = Engine running, FE not running
  LinBus->LinMessage[1] = 0xFF;
  // Brightness SwitchPOsition -> 0x86 to 0xDC dimming range
  LinBus->LinMessage[2] = 0x86;
  // Static value:
  LinBus->LinMessage[3] = 0x7F;
  LinBus->writeFrame(0x0D, 4);
  this->setKey(this->lastKeyPressed);
}

void MQBService::checkLastKey(byte linKey) {
  for (std::map<String, byte>::iterator it = mqbKeyArray.begin(); it != mqbKeyArray.end(); ++it) {
    String name = it->first;
    byte keyId = it->second;
    if (keyId == linKey) {
      lastKeyPressed = name;
    }
  }
}

void MQBService::readLinData(uint8_t frameId) {
  bool chkSumValid = LinBus->readFrame(frameId);
  if (chkSumValid) {
    // dumpBuffer();
    if (frameId == 0x0E && LinBus->LinMessage[1] != 0x00) {
      uint8_t linMessage = LinBus->LinMessage[1];
      // Serial.printf("Valid Message1 : %02X \n", linMessage);
      checkLastKey(linMessage);
    }
    if (frameId == 0x0F && LinBus->LinMessage[2] != 0x80) {
      uint8_t linMessage = LinBus->LinMessage[2];
      // Serial.printf("Valid Message2 : %02X \n", linMessage);
      checkLastKey(linMessage);
    }
    // Special Treatment of On/Off Key:
    if (frameId == 0x0F && LinBus->LinMessage[3] == 0x2A) {
      lastKeyPressed = "MQB_ONOFF";
    }
    // Special Treatment of Horn Key:
    if (frameId == 0x0E && LinBus->LinMessage[7] == 0x02) {
      lastKeyPressed = "MQB_HORN";
    }
    // Special Treatment of Temp Message:
    if (frameId == 0x3A) {
      this->temp = LinBus->LinMessage[0];
    }
  }
}
