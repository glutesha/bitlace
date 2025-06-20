#include "settings.h"

void save_settings(JsonDocument &settingsDoc){
  File settingsFile = LittleFS.open("/settings.json", "w");
  serializeJson(settingsDoc, settingsFile);
  settingsFile.close();
}
