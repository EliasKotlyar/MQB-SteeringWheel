
#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>
#include <Lin_Interface.h>
#include <DebugService.h>
#define DEFAULT_KEYPRESSED_STATE 0

#ifndef PQService_h
#define PQService_h
class PQSlaveState {
 public:
  String keyPressed;
  int temp;

  static void read(PQSlaveState& settings, JsonObject& root) {
    root["keyPressed"] = settings.keyPressed;
    root["temp"] = settings.temp;
  }

  static StateUpdateResult update(JsonObject& root, PQSlaveState& PQSlaveState) {
    // No Change
    return StateUpdateResult::UNCHANGED;
  }
};

class PQSlave : public StatefulService<PQSlaveState> {
 public:
  PQSlave(AsyncWebServer* server, SecurityManager* securityManager, Lin_Interface* lin, DebugService* debugService);
  void setup();
  void loop();
  void begin();
  void setKey(String key);

 private:
  // Funcs:
  static void startTaskImpl(void* _this);
  void processData(byte protectedId);
  byte getKeyIDByName(String name);
  // Vars:
  HttpEndpoint<PQSlaveState> _httpEndpoint;
  WebSocketTxRx<PQSlaveState> _webSocket;
  Lin_Interface* LinBus;
  DebugService* debugService;

  // Key Mappings
  std::map<String, byte> PQKeyArray = {
      // Left Side:
      {"PQ_VOL_PLUS", 0x06},
      {"PQ_VOL_MINUS", 0x07},
      {"PQ_LEFT", 0x03},
      {"PQ_RIGHT", 0x02},
      {"PQ_TEL", 0x1A},
      {"PQ_MIC", 0x2B},
      // Right Side:
      {"PQ_UP", 0x22},
      {"PQ_DOWN", 0x23},
      {"PQ_PREV", 0x09},
      {"PQ_NEXT", 0x0A},
      {"PQ_OK", 0x28},
      {"PQ_RET", 0x29},
      {"PQ_NONE", 0x0},
      {"PQ_HORN", 0x0}
  };
  uint8_t buttons_response[8] = {0xFF, 0x00, 0xFF, 0xF0, 0x60, 0x00, 0x30, 0x00};
  static const uint8_t BUTTONS_ID = 0x0E;
  static const uint8_t LIGHT_ID = 0x0D;
};
#endif