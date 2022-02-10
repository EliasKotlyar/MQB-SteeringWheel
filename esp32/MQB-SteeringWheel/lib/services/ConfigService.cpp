#include <ConfigService.h>

ConfigService::ConfigService(AsyncWebServer* server, SecurityManager* securityManager, FS* fs) :

    _httpEndpoint(ConfigState::read,
                  ConfigState::update,
                  this,
                  server,
                  "/rest/ConfigState",
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(ConfigState::read,
               ConfigState::update,
               this,
               server,
               "/ws/ConfigState",
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED),
    _fsPersistence(ConfigState::read, ConfigState::update, this, fs, CONFIG_SETTINGS_FILE) {
  // configure settings service update handler to update LED state
  addUpdateHandler(
      [&](const String& originId) {
         Serial.print("Updated State from ");
         Serial.print(originId);
         Serial.println();

        //onConfigUpdated();
      },
      false);
}

void ConfigService::begin() {
  _fsPersistence.readFromFS();
}
