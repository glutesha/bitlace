#include "saves.h"

void load_saves(AsyncWebServer &server){
    server.on("/api/server", HTTP_GET, [](AsyncWebServerRequest *request){
        File saves = LittleFS.open("saves.json", "r");
        if(!saves){
            request->send(404, "text/plain", "Saves not found");
        }
        request->send(200, "application/json", saves.readString());
    });}