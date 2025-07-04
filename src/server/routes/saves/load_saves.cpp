#include "saves.h"

void load_saves(AsyncWebServer &server){
    server.on("/api/saves", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/saves.json", "application/json");
    });}