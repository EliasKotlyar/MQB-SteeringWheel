
#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>
#include <Lin_Interface.h>
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
  MQBService(AsyncWebServer* server, SecurityManager* securityManager, Lin_Interface* lin);
  void setup();
  void loop();
  void begin();

 private:
  HttpEndpoint<MQBState> _httpEndpoint;
  WebSocketTxRx<MQBState> _webSocket;
  Lin_Interface* LinBus;

  void registerConfig();
  void onConfigUpdated();

  void readLinData(uint8_t frameId);
  String lastKeyPressed;
  void dumpBuffer();
  uint8_t lightValue = 255;
  uint8_t temp = 0;
  void checkLastKey(byte linKey);
  
  std::map<String, byte> mqbKeyArray = {
      {"MQB_NONE", 0x00},
      {"MQB_RESET", 0x88},
      {"MQB_PLUS", 0x82},
      {"MQB_ACC", 0xB0},
      {"MQB_MINUS", 0x84},
      {"MQB_SET", 0x81},
      {"MQB_SHAKE", 0x0C},
      {"MQB_VOL_PLUS", 0x10},
      {"MQB_VOL_MINUS", 0x11},
      // Right Side:
      {"MQB_SPEAK", 0x19},
      {"MQB_UP", 0x04},
      {"MQB_LEFT", 0x03},
      {"MQB_OK", 0x07},
      {"MQB_RIGHT", 0x02},
      {"MQB_VIEW", 0x23},
      {"MQB_DOWN", 0x05},
      {"MQB_FORWARD", 0x16},
      {"MQB_REVERSE", 0x15},
  };

  void getLastKeyCode();

  uint8_t getTemp();

  String getLastKey();
  bool hasKeysPressed();
  void setKey(String key);
};
