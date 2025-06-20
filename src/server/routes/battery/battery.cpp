#include "battery.h"

void battery(AsyncWebServer &server, JsonDocument &settingsDoc){
server.on("/api/battery", HTTP_GET, [&settingsDoc](AsyncWebServerRequest *request){
    String response = String(read_battery_percentage(settingsDoc["battery"]));
    request->send(200, "text/plain", response);
});}
