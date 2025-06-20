#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

#include "captive_portal/captive.h"
void app(AsyncWebServer &server);