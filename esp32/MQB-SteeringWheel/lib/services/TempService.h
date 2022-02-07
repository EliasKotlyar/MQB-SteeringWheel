#ifndef TempService_h
#define TempService_h

#include <MQB_Interface.hpp>
#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>

#define DEFAULT_Temp_STATE 0


class TempState {
 public:
  int pin;

  static void read(TempState& settings, JsonObject& root) {
    root["pin"] = settings.pin;
  }

  static StateUpdateResult update(JsonObject& root, TempState& TempState) {
    int newState = root["pin"];
    if (TempState.pin != newState) {
      TempState.pin = newState;
      return StateUpdateResult::CHANGED;
    }
    return StateUpdateResult::UNCHANGED;
  }
};

class TempService : public StatefulService<TempState> {
 public:
  TempService(AsyncWebServer* server, SecurityManager* securityManager);
  void begin();
  void setNumber(byte key);

 private:
  HttpEndpoint<TempState> _httpEndpoint;
  WebSocketTxRx<TempState> _webSocket;

  void registerConfig();
  void onConfigUpdated();
  void triggerPin(byte pinNr);
  void setPin(byte data);
};

#endif
