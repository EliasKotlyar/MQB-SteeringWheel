#ifndef DebugService_h
#define DebugService_h

#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>

#define DEFAULT_KEYPRESSED_STATE 0

class DebugState {
 public:
  bool enabled = false;

  static void read(DebugState& settings, JsonObject& root) {
    root["enabled"] = settings.enabled;
  }

  static StateUpdateResult update(JsonObject& root, DebugState& DebugState) {
    int newState = root["enabled"];
    if (DebugState.enabled != newState) {
      DebugState.enabled = newState;
      return StateUpdateResult::CHANGED;
    }
    return StateUpdateResult::UNCHANGED;
  }
};

class DebugService : public StatefulService<DebugState> {
 public:
  DebugService(AsyncWebServer* server, SecurityManager* securityManager);
  void begin();

 private:
  HttpEndpoint<DebugState> _httpEndpoint;
  WebSocketTxRx<DebugState> _webSocket;

  void registerConfig();
  void onConfigUpdated();
};

#endif
