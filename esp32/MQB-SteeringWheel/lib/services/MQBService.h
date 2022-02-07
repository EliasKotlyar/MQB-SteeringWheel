#ifndef MQBService_h
#define MQBService_h

#include <MQB_Interface.hpp>
#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>

#define DEFAULT_KEYPRESSED_STATE 0

class MQBState {
 public:
  String lastKeyPressed;
  int temp;

  static void read(MQBState& settings, JsonObject& root) {
    root["lastKeyPressed"] = settings.lastKeyPressed;
    root["temp"] = settings.temp;
  }

  static StateUpdateResult update(JsonObject& root, MQBState& MQBState) {
    // No Change
    return StateUpdateResult::UNCHANGED;
  }
};

class MQBService : public StatefulService<MQBState> {
 public:
  MQBService(AsyncWebServer* server, SecurityManager* securityManager);
  void begin();
  void setKey(String key);

 private:
  HttpEndpoint<MQBState> _httpEndpoint;
  WebSocketTxRx<MQBState> _webSocket;

  void registerConfig();
  void onConfigUpdated();
};

#endif
