#include <MQBService.h>

MQBService::MQBService(AsyncWebServer* server, SecurityManager* securityManager) :
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
  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
}

void MQBService::begin() {
  _state.lastKeyPressed = MQB_NONE;
  onConfigUpdated();
}

void MQBService::onConfigUpdated() {
  // Calls if value updates
}

void MQBService::registerConfig() {
}

void MQBService::setKey(byte key) {
  this->update(
      [&](MQBState& state) {
        if (state.lastKeyPressed == key) {
          return StateUpdateResult::UNCHANGED;
        }
        if (key != MQB_NONE) {
          String keyStr = MQB_Interface::getKeyName(key);
          Serial.println("Key Pressed " + keyStr);
        }
        state.lastKeyPressed = key;
        return StateUpdateResult::CHANGED;
      },
      "setkeymethod");
}
