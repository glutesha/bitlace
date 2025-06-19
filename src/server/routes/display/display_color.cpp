#include "display_color.h"

void display_color(AsyncWebServer &server, Display &current){
server.on("/api/display_color", HTTP_GET, [&current](AsyncWebServerRequest *request){
    String color = current.getColor();
    request->send(200, "text/plain", color);
});}