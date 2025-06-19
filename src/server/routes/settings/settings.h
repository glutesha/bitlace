#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void settings_form(AsyncWebServer &server, JsonDocument &settingsDoc);