

#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>
#include <FSPersistence.h>

#include <MQBService.h>
#include <PQSlave.h>
#define DEFAULT_Config_STATE 0

#define CONFIG_SETTINGS_FILE "/config/config.json"
class ConfigState {
 public:
  String config;
  DynamicJsonDocument jsonDocument = DynamicJsonDocument(2000);

  static void read(ConfigState& settings, JsonObject& root) {
    JsonObjectConst object = settings.jsonDocument.to<JsonObject>();
    root.set(object);
  }

  static StateUpdateResult update(JsonObject& root, ConfigState& settings) {
    // Serial.println("Got Update");

    // configState.config = root;
    // serializeJson(configState.config, Serial);

    // JsonObject root = jsonDocument.to<JsonObject>();
    // deserializeJson(root, settings.config,2000);
    settings.jsonDocument.set(root);
    // Send to Serial:
    // serializeJson(settings.jsonDocument, Serial);

    return StateUpdateResult::CHANGED;
  }
};

class ConfigService : public StatefulService<ConfigState> {
 public:
  ConfigService(AsyncWebServer* server, SecurityManager* securityManager, FS* fs, MQBService* mqb, PQSlave* pq);
  void begin();

 private:
  HttpEndpoint<ConfigState> _httpEndpoint;
  WebSocketTxRx<ConfigState> _webSocket;
  FSPersistence<ConfigState> _fsPersistence;

  MQBService* mqb;
  PQSlave* pq;
  String getMapping(String pqKeyNumber);
};


