#include "display_update.h"

void display_update(AsyncWebServer &server, Display &current){
server.on("/api/display", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [&current](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    String body;
    for (size_t i = 0; i < len; i++) {
      body += (char)data[i];
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, body);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      request->send(400, "text/plain", "Bad Request");
      return;
    }

    if (!doc.is<JsonArray>()) {
      request->send(400, "text/plain", "Expected JSON array");
      return;
    }

    JsonArray display = doc.as<JsonArray>();
    current.drawArray(display);
    save_state(current);
    request->send(200, "text/plain", "Display updated");
  });}