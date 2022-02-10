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
  _state.enabled = 0;
  _state.adc_sampling_freq = 1000;
}

void TempService::loop() {
  int startTime = 0;
  while (1) {
    delay(_state.adc_sampling_freq);
    _state.adc_value = analogRead(SHZ_CS);
  }
}
void TempService::onConfigUpdated() {
  digitalWrite(SHZ_INP, _state.enabled);
}
