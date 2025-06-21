#include "state.h"

void load_state(Display &current){
  File stateFile = LittleFS.open("/state.json", "r");
  if(!stateFile){
    Serial.println("No file!");
    return;
  }
  JsonDocument stateDoc;
  DeserializationError err = deserializeJson(stateDoc, stateFile);
  if(err){
    Serial.print("state deserializeJson() ");
    Serial.println(err.c_str());
    return;
  }
  JsonArray arr = stateDoc.as<JsonArray>();
  current.drawArray(arr);
  stateFile.close();
  Serial.println("Loaded state!");
}