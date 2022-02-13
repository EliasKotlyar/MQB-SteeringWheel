#include <ServiceManager.h>

ServiceManager services;
void setup() {
  services.setup();
}

void loop() {
  /*
  // run the framework's loop function
  */
 services.loop();
}
