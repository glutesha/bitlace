#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "battery/battery.h"

void battery(AsyncWebServer &server, JsonDocument &settingsDoc);