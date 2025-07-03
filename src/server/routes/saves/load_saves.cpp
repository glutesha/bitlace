#include "saves.h"

void load_saves(AsyncWebServer &server){
    server.on("/api/saves", HTTP_GET, [](AsyncWebServerRequest *request){
        File saves = LittleFS.open("/saves.json", "r");

        if(!saves){
            request->send(404, "text/plain", "Saves not found");
            return;
        }

        request->send(200, "application/json", saves.readString());
        saves.close();
    });}