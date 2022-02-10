#include <ServiceManager.h>

/*
void pqLoop(void* parameter) {
  pq.loop();
}
*/
ServiceManager services;
void setup() {
  
  services.setup();

  /*
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

  */
 services.loop();
}
