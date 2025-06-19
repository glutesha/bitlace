#pragma once
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

class CaptiveRequestHandler : public AsyncWebHandler {
public:
    CaptiveRequestHandler();
    virtual ~CaptiveRequestHandler();
    bool canHandle(AsyncWebServerRequest *request);
    void handleRequest(AsyncWebServerRequest *request);
};