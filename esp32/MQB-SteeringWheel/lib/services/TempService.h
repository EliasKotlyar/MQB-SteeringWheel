#ifndef TempService_h
#define TempService_h


#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>

#define SHZ_CS 27 
#define SHZ_ENABLE 21 // Diag PIN
#define SHZ_INP 19 // ON/OFf Pin


class TempState {
 public:
  byte enabled;
  int adc_value; 
  int adc_sampling_freq;


  static void read(TempState& settings, JsonObject& root) {
    root["enabled"] = settings.enabled;
    root["adc_value"] = settings.adc_value;
  }

  static StateUpdateResult update(JsonObject& root, TempState& TempState) {
    byte newState = root["enabled"];
    if (TempState.enabled != newState) {
      TempState.enabled = newState;
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

  void loop();
  void onConfigUpdated();  
};

#endif
