#include "main.h"

void main(AsyncWebServer &server) {
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/dist/index.html", "text/html");
    });

    server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/dist/settings/index.html", "text/html");
    });

    server.serveStatic("/", LittleFS, "/dist/");

    server.addHandler(new CaptiveRequestHandler());

     server.onNotFound([](AsyncWebServerRequest *request){
        request->send(LittleFS, "/dist/index.html", "text/html");
});}