#include "state.h"

void save_state(Display &current){
  File stateFile = LittleFS.open("/state.json", "w");
  JsonDocument stateDoc;
  bool (&state)[8][8] = current.getState();
  JsonArray arr = stateDoc.to<JsonArray>();
  for (int i = 0; i < 8; ++i) {
    JsonArray row = arr.add<JsonArray>();
    for (int j = 0; j < 8; ++j) {
      row.add(state[i][j]); 
    }
  }

  serializeJson(stateDoc, stateFile);
  stateFile.close();
}
