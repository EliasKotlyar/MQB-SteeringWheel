
#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>
#include <Lin_Interface.h>
#define DEFAULT_KEYPRESSED_STATE 0

class PQMasterState {
 public:
  String lastKeyPressed;
  int temp;

  static void read(PQMasterState& settings, JsonObject& root) {
    root["lastKeyPressed"] = settings.lastKeyPressed;
    root["temp"] = settings.temp;
  }

  static StateUpdateResult update(JsonObject& root, PQMasterState& PQMasterState) {
    // No Change
    return StateUpdateResult::UNCHANGED;
  }
};

class PQMasterService : public StatefulService<PQMasterState> {
 public:
  PQMasterService(AsyncWebServer* server, SecurityManager* securityManager, Lin_Interface* lin);
  void setup();
  void loop();
  void begin();

 private:
  HttpEndpoint<PQMasterState> _httpEndpoint;
  WebSocketTxRx<PQMasterState> _webSocket;
  Lin_Interface* LinBus;

  void registerConfig();
  void onConfigUpdated();

  void readLinData(uint8_t frameId);
  String lastKeyPressed;
  void dumpBuffer();
  uint8_t lightValue = 255;
  uint8_t temp = 0;
  void checkLastKey(byte linKey);
  
  std::map<String, byte> PQMasterKeyArray = {
      {"PQMaster_NONE", 0x00},
      {"PQMaster_RESET", 0x88},
      {"PQMaster_PLUS", 0x82},
      {"PQMaster_ACC", 0xB0},
      {"PQMaster_MINUS", 0x84},
      {"PQMaster_SET", 0x81},
      {"PQMaster_SHAKE", 0x0C},
      {"PQMaster_VOL_PLUS", 0x10},
      {"PQMaster_VOL_MINUS", 0x11},
      // Right Side:
      {"PQMaster_SPEAK", 0x19},
      {"PQMaster_UP", 0x04},
      {"PQMaster_LEFT", 0x03},
      {"PQMaster_OK", 0x07},
      {"PQMaster_RIGHT", 0x02},
      {"PQMaster_VIEW", 0x23},
      {"PQMaster_DOWN", 0x05},
      {"PQMaster_FORWARD", 0x16},
      {"PQMaster_REVERSE", 0x15},
  };

  

  void getLastKeyCode();

  uint8_t getTemp();

  String getLastKey();
  bool hasKeysPressed();
  void setKey(String key);
};
