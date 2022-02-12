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
}

void DebugService::begin() {
  _state.enabled = true;
  _state.bufferLen = 0;
}

void DebugService::loop() {
}

void DebugService::addLinMessage(byte protectedId, byte* buffer, byte bufferlen) {
  this->update(
      [&](DebugState& state) {
        state.protectedId = protectedId;
        memcpy(state.buffer, buffer, bufferlen);
        state.bufferLen = bufferlen;
        return StateUpdateResult::CHANGED;
      },
      "addLinMessage");
}
