#include <ConfigService.h>

ConfigService::ConfigService(AsyncWebServer* server,
                             SecurityManager* securityManager,
                             FS* fs,
                             MQBService* mqb,
                             PQSlave* pq) :

    _httpEndpoint(ConfigState::read,
                  ConfigState::update,
                  this,
                  server,
                  "/rest/ConfigState",
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(ConfigState::read,
               ConfigState::update,
               this,
               server,
               "/ws/ConfigState",
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED),
    _fsPersistence(ConfigState::read, ConfigState::update, this, fs, CONFIG_SETTINGS_FILE) {
  // configure settings service update handler to update LED state
  addUpdateHandler(
      [&](const String& originId) {
        Serial.print("Updated State from ");
        Serial.print(originId);
        Serial.println();

        // onConfigUpdated();
      },
      false);
  this->mqb = mqb;
  this->pq = pq;
}

void ConfigService::begin() {
  //update_handler_id_t myUpdateHandler = 
  this->mqb->addUpdateHandler([&](const String& originId) {
    this->mqb->read([&](MQBState& mqbState) {
      String mapping = this->getMapping(mqbState.lastKeyPressed);
      /*
      Serial.println("MQB Key Pressed:");
      Serial.println(mqbState.lastKeyPressed);
      Serial.println("PQ Key Pressed:");
      Serial.println(mapping);
      */

      this->pq->update(
          [&](PQSlaveState& pqState) {
            pqState.keyPressed = mapping;
            return StateUpdateResult::CHANGED;  // notify StatefulService by returning CHANGED
          },
          "config");
    });
  });

  //_fsPersistence.readFromFS();
}
String ConfigService::getMapping(String mqbKeyNumber) {
  std::map<String, String> mappingArray = {
      {"MQB_NONE", "PQ_NONE"},
      {"MQB_RESET", "PQ_NONE"},
      {"MQB_PLUS", "PQ_NONE"},
      {"MQB_ACC", "PQ_NONE"},
      {"MQB_MINUS", "PQ_NONE"},
      {"MQB_SET", "PQ_NONE"},
      {"MQB_SHAKE", "PQ_TEL"},
      {"MQB_VOL_PLUS", "PQ_VOL_PLUS"},
      {"MQB_VOL_MINUS", "PQ_VOL_MINUS"},
      // Right Side:
      {"MQB_SPEAK", "PQ_MIC"},
      {"MQB_UP", "PQ_UP"},
      {"MQB_LEFT", "PQ_LEFT"},
      {"MQB_OK", "PQ_OK"},
      {"MQB_RIGHT", "PQ_RIGHT"},
      {"MQB_VIEW", "PQ_RET"},
      {"MQB_DOWN", "PQ_DOWN"},
      {"MQB_FORWARD", "PQ_NEXT"},
      {"MQB_REVERSE", "PQ_PREV"},
      {"MQB_HORN", "PQ_HORN"},
  };
  String ret = "PQ_NONE";
  for (std::map<String, String>::iterator it = mappingArray.begin(); it != mappingArray.end(); ++it) {
    String mqbName = it->first;
    String pqName = it->second;
    if (mqbKeyNumber == mqbName) {
      ret = pqName;
      break;
    }
  }

  // pqmaster.loop();

  // String key = mqb.getLastKey();
  /*
  byte keyNumber = 0;
  if (key == "MQB_MINUS") {
    keyNumber = 6;
  }

  shiftRegService.setNumber(keyNumber);
  */
  // mqbStateService.setKey(key);
  return ret;
}