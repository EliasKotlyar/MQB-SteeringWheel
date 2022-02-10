#include <ServiceManager.h>

/*
void pqLoop(void* parameter) {
  pq.loop();
}
*/

void setup() {
  /*
  startServices();
  xTaskCreate(pqLoop,        // Function that should be called
              "Toggle LED",  // Name of the task (for debugging)
              1000,          // Stack size (bytes)
              NULL,          // Parameter to pass
              1,             // Task priority
              NULL           // Task handle
  );
  */
}

void loop() {
  /*
  // run the framework's loop function
  esp8266React.loop();
  mqb.loop();

  String key = mqb.getLastKey();
  byte keyNumber = 0;
  if (key == "MQB_MINUS") {
    keyNumber = 6;
  }
  if (key == "MQB_PLUS") {
    keyNumber = 7;
  }
  shiftRegService.setNumber(keyNumber);
  mqbStateService.setKey(key);
  */
}
