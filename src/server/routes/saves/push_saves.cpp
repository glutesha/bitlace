#include "saves.h"

void push_saves(AsyncWebServer &server){
    server.on("/api/saves", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
        
        if (index == 0) {
            if(LittleFS.totalBytes() - LittleFS.usedBytes() <= request->contentLength()){
                File error = LittleFS.open("/dist/error/index.html", "r");
                String errorpage = error.readString();
                errorpage.replace("{ErrorMsg}", "500 No LittleFS memory available!");
                request->send(500, "text/html", errorpage);
                error.close();
                return;
            }

            File *saves = new File(LittleFS.open("/saves.json", "w"));
            request->_tempObject = saves;
        }

        File *saves = static_cast<File *>(request->_tempObject);
        if (saves && *saves) {
            saves->write(data, len);
        }
        
        if (index + len == total) {
            if (saves) {
                saves->close();
                delete saves;
                request->_tempObject = nullptr;
            }
            request->send(200, "text/plain", "Saved!");
        }
    });}