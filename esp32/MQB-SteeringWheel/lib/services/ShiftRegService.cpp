#include <ShiftRegService.h>

ShiftRegService::ShiftRegService(AsyncWebServer* server,
                                     SecurityManager* securityManager) :
    _httpEndpoint(ShiftRegState::read,
                  ShiftRegState::update,
                  this,
                  server,
                  "/rest/ShiftRegState",
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(ShiftRegState::read,
               ShiftRegState::update,
               this,
               server,
               "/ws/ShiftRegState",
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED)
 {

  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String& originId) { 
    //Serial.print("Updated State from ");
    //Serial.print(originId);
    //Serial.println();

    onConfigUpdated(); 
    }, false);
}

void ShiftRegService::begin() {
  _state.pin = DEFAULT_SHIFTREG_STATE;
  onConfigUpdated();
}

void ShiftRegService::onConfigUpdated() {
  if(_state.pin == 0){
    this->setPin(0);
  }else{
    byte x = 0;   
    bitSet(x, (_state.pin - 1));
    this->setPin(x);
  }  
}

void ShiftRegService::registerConfig() {
 
}

void ShiftRegService::setPin(byte data)
{
  digitalWrite(PIN_STORE, LOW);

  //int ledPattern[8] = {1, 1, 1, 1, 1, 1, 1, 1};
  //int ledPattern[8] = {1, 0, 0, 0, 0, 0, 0, 1};

  /*
  for (int i=0; i<8; i++) {
    // set shift pin to "wait"
     digitalWrite(PIN_SHIFT, LOW);
    // writing to data pin
    digitalWrite(PIN_DATA, ledPattern[i]);
    // rising slope -> shifting data in the register
    digitalWrite(PIN_SHIFT, HIGH);
  }
  */

  shiftOut(PIN_DATA, PIN_SHIFT, MSBFIRST, data);

  

  // Shift out LED:
  //shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, data);
  digitalWrite(PIN_STORE, HIGH);
}