#include "settings.h"

void load_settings(JsonDocument &settingsDoc){
  bool loaderr = false;
  File settingsFile = LittleFS.open("/settings.json", "r");
  if(!settingsFile){
    Serial.println("No file!");
    loaderr = true;
  }
  DeserializationError err = deserializeJson(settingsDoc, settingsFile);
  if(err){
    Serial.print("settings deserializeJson() ");
    Serial.println(err.c_str());
    loaderr = true;
  }
  if(loaderr){
    settingsDoc["ssid"] = SSID;
    settingsDoc["password"] = PASSWORD;
    settingsDoc["hidden"] = HIDDEN;
    settingsDoc["channel"] = CHANNEL;
    settingsDoc["color"] = DISPLAY_COLOR;
    settingsDoc["brightness"] = BRIGHTNESS;
    settingsDoc["data"] = DATA;
    settingsDoc["clk"] = CLK;
    settingsDoc["cs"] = CS;
    settingsDoc["battery"] = BATTERY;
    settingsDoc["button"] = BUTTON;
    settingsDoc["resistance"] = BATTERY_RESISTANCE_RATIO;
    return;
  }

  Serial.println("Loaded settings!");
  settingsFile.close();
}
