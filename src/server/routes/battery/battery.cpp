#include "battery.h"

void battery(AsyncWebServer &server, Battery &power){
server.on("/api/battery", HTTP_GET, [&power](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(power.level()));
});}
