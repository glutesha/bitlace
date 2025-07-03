#include "saves.h"

void push_saves(AsyncWebServer &server){
    server.on("/api/server", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
        File saves = LittleFS.open("saves.json", "w");
        String body;

        for (size_t i = 0; i < len; i++) {
            body += (char)data[i];
        }

        // LittleFS.totalBytes() - LittleFS.usedBytes() <= request.;
        request->send(200, "text/plain", "Saved!");
    });}