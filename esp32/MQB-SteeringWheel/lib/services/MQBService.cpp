#include <MQBService.h>

MQBService::MQBService(AsyncWebServer* server,
                                     SecurityManager* securityManager) :
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
               AuthenticationPredicates::IS_AUTHENTICATED)
 {

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
}

void MQBService::begin() {
  _state.lastKeyPressed = DEFAULT_KEYPRESSED_STATE;
  onConfigUpdated();
}

void MQBService::onConfigUpdated() {
  // Calls if value updates
}

void MQBService::registerConfig() {
 
}
