#include "display_state.h"

void display_state(AsyncWebServer &server, Display &current){
server.on("/api/display", HTTP_GET, [&current](AsyncWebServerRequest *request){
    JsonDocument response;
    bool (&state)[8][8] = current.getState();
    JsonArray arr = response.to<JsonArray>();
    for (int i = 0; i < 8; ++i) {
      JsonArray row = arr.add<JsonArray>();
      for (int j = 0; j < 8; ++j) {
        row.add(state[i][j]); 
      }
    }
    String result;
    serializeJson(response, result);
    request->send(200, "application/json", result);
});}