#include "saves.h"

void push_saves(AsyncWebServer &server){
    server.on("/api/server", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
        File saves = LittleFS.open("saves.json", "w");
        File error = LittleFS.open("/dist/error/index.html", "r");
        String errorpage = error.readString();

        String body;

        for (size_t i = 0; i < len; i++) {
            body += (char)data[i];
        }

        if(LittleFS.totalBytes() - LittleFS.usedBytes() <= request->contentLength()){
            errorpage.replace("{ErrorMsg}", "500 No LittleFS memory available!");
            request->send(500, "text/html", errorpage);
            saves.close();
            error.close();
            return;
        }
        
        request->send(200, "text/plain", "Saved!");
        saves.close();
        error.close();
    });}