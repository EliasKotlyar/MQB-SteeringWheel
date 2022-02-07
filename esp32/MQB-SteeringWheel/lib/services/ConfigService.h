#ifndef ConfigService_h
#define ConfigService_h

#include <MQB_Interface.hpp>
#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>
#include <FSPersistence.h>
#define DEFAULT_Config_STATE 0

#define CONFIG_SETTINGS_FILE "/config/config.json"
class ConfigState {
 public:
  int pin;

  static void read(ConfigState& settings, JsonObject& root) {
    root["pin"] = settings.pin;
  }

  static StateUpdateResult update(JsonObject& root, ConfigState& ConfigState) {
    int newState = root["pin"];
    if (ConfigState.pin != newState) {
      ConfigState.pin = newState;
      return StateUpdateResult::CHANGED;
    }
    return StateUpdateResult::UNCHANGED;
  }
};

class ConfigService : public StatefulService<ConfigState> {
 public:
  ConfigService(AsyncWebServer* server, SecurityManager* securityManager, FS* fs);
  void begin();
  void setNumber(byte key);

 private:
  HttpEndpoint<ConfigState> _httpEndpoint;
  WebSocketTxRx<ConfigState> _webSocket;
  FSPersistence<ConfigState> _fsPersistence;

  void registerConfig();
  void onConfigUpdated();
  void triggerPin(byte pinNr);
  void setPin(byte data);
};

#endif
