#include "battery.h"

void battery(AsyncWebServer &server, JsonDocument &settingsDoc){
server.on("/api/battery", HTTP_GET, [&settingsDoc](AsyncWebServerRequest *request){
    request->send(200, String(read_battery_percentage(settingsDoc["battery"])));
});}
