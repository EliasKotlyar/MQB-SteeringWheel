#ifndef ShiftRegService_h
#define ShiftRegService_h

#include <MQB_Interface.hpp>
#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>

#define DEFAULT_SHIFTREG_STATE 0
#define PIN_LATCH 16 // SHIFT_SHCP
#define PIN_CLOCK 17 // SHIFT_STCP
#define PIN_DATA 18 // SHIFT_DS



#define PIN_SHIFT PIN_LATCH   // connected to SHCP
#define PIN_STORE PIN_CLOCK   // connected to STCP





class ShiftRegState {
 public:
  int pin;

  static void read(ShiftRegState& settings, JsonObject& root) {
    root["pin"] = settings.pin;
  }

  static StateUpdateResult update(JsonObject& root, ShiftRegState& ShiftRegState) {
    int newState = root["pin"];
    //serializeJson(root, Serial);

    //Serial.println("Update 1!");
    //Serial.println(newState);
    //Serial.println(ShiftRegState.pin);

    if (ShiftRegState.pin != newState) {
      ShiftRegState.pin = newState;
      return StateUpdateResult::CHANGED;
    }
    return StateUpdateResult::UNCHANGED;
  }


};

class ShiftRegService : public StatefulService<ShiftRegState> {
 public:
  ShiftRegService(AsyncWebServer* server,
                    SecurityManager* securityManager);
  void begin();

 private:
  HttpEndpoint<ShiftRegState> _httpEndpoint;
  WebSocketTxRx<ShiftRegState> _webSocket;


  void registerConfig();
  void onConfigUpdated();
  void triggerPin(byte pinNr);
  void setPin(byte data);
};

#endif
