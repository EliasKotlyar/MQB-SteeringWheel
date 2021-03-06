#ifndef DebugService_h
#define DebugService_h

#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>

#define DEFAULT_KEYPRESSED_STATE 0

class DebugState {
 public:
  bool enabled = false;
  int protectedId;
  byte buffer[8];
  byte bufferLen;

  static void read(DebugState& settings, JsonObject& root) {
    root["enabled"] = settings.enabled;
    String protectedID = "0x" + String(settings.protectedId, HEX);
    String buffer = "";
    
    for (byte i = 0; i < settings.bufferLen; i++) {
      char charBuffer[20];
      //formatieren des Textes und ablegen in dem Array
      sprintf(charBuffer, "%02X", settings.buffer[i]);
      buffer = buffer + charBuffer;
    }
    root["protectedId"] = protectedID;
    root["buffer"] = buffer;
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
  void addLinMessage(byte protectedId, byte* buffer, byte bufferlen);
  void loop();

 private:
  HttpEndpoint<DebugState> _httpEndpoint;
  WebSocketTxRx<DebugState> _webSocket;

  void registerConfig();
  void onConfigUpdated();
};

#endif
