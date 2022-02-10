#include <DebugService.h>

DebugService::DebugService(AsyncWebServer* server, SecurityManager* securityManager) :
    _httpEndpoint(DebugState::read,
                  DebugState::update,
                  this,
                  server,
                  "/rest/DebugState",
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(DebugState::read,
               DebugState::update,
               this,
               server,
               "/ws/DebugState",
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
}

void DebugService::begin() {
  _state.enabled = false;
  onConfigUpdated();
}

void DebugService::onConfigUpdated() {
  // Calls if value updates
}

void DebugService::addLinMessage(byte protectedId, byte* buffer, byte bufferlen) {
  this->update(
      [&](DebugState& state) {
        state.protectedId = protectedId;

        return StateUpdateResult::CHANGED;
      },
      "setkeymethod");
}
