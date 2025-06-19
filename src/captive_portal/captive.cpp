#include "captive.h"

CaptiveRequestHandler::CaptiveRequestHandler() {}
CaptiveRequestHandler::~CaptiveRequestHandler() {}
  
bool CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request){
    return true;
}
  
void CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request) {
    request->send(LittleFS, "/dist/index.html", "text/html");
}
