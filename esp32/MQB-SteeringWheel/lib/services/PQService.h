
#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>
#include <Lin_Interface.h>
#include <DebugService.h>
#define DEFAULT_KEYPRESSED_STATE 0

class PQState {
 public:
  String lastKeyPressed;
  int temp;

  static void read(PQState& settings, JsonObject& root) {
    root["lastKeyPressed"] = settings.lastKeyPressed;
    root["temp"] = settings.temp;
  }

  static StateUpdateResult update(JsonObject& root, PQState& PQState) {
    // No Change
    return StateUpdateResult::UNCHANGED;
  }
};

class PQService : public StatefulService<PQState> {
 public:
  PQService(AsyncWebServer* server, SecurityManager* securityManager, Lin_Interface* lin, DebugService* debugService);
  void setup();
  void loop();
  void begin();

 private:
  HttpEndpoint<PQState> _httpEndpoint;
  WebSocketTxRx<PQState> _webSocket;
  Lin_Interface* LinBus;
  DebugService* debugService;

  void registerConfig();
  void onConfigUpdated();

  void readLinData(uint8_t frameId);
  String lastKeyPressed;
  void dumpBuffer();
  uint8_t lightValue = 255;
  uint8_t temp = 0;
  void checkLastKey(byte linKey);
  static void startTaskImpl(void* _this);

  std::map<String, byte> PQKeyArray = {

      {"PQ_PREV", 0x16},
      {"PQ_Next", 0x15},
      {"PQ_PhoneVoiceMic", 0x19},
      {"PQ_Phone", 0x1C},
      {"PQ_View", 0x23},
      {"PQ_Up", 0x04},
      {"PQ_Down", 0x05},
      {"PQ_SrcMinus", 0x02},
      {"PQ_SrcPlus", 0x07},
  };
  uint8_t buttons_response[8] = {0xFF, 0x00, 0xFF, 0xF0, 0x60, 0x00, 0x30, 0x00};
  static const uint8_t BUTTONS_ID = 0x0E;
  static const uint8_t LIGHT_ID = 0x0D;
  void getLastKeyCode();

  uint8_t getTemp();

  String getLastKey();
  bool hasKeysPressed();
  void setKey(String key);

  void processData(byte protectedId);
  byte getKeyIDByName(String name);
};
