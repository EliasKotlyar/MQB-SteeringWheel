#include <TempService.h>

TempService::TempService(AsyncWebServer* server, SecurityManager* securityManager) :
    _httpEndpoint(TempState::read,
                  TempState::update,
                  this,
                  server,
                  "/rest/TempState",
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(TempState::read,
               TempState::update,
               this,
               server,
               "/ws/TempState",
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  // configure settings service update handler to update LED state
  addUpdateHandler(
      [&](const String& originId) {
        // Serial.print("Updated State from ");
        // Serial.print(originId);
        // Serial.println();

        onConfigUpdated();
      },
      false);
}

void TempService::begin() {
  _state.pin = DEFAULT_Temp_STATE;
  onConfigUpdated();
}

void TempService::registerConfig() {
}

void TempService::setNumber(byte key) {
  this->update(
      [&](TempState& state) {
        if (state.pin == key) {
          return StateUpdateResult::UNCHANGED;
        }
        state.pin = key;
        return StateUpdateResult::CHANGED;
      },
      "setkeymethod");
}
