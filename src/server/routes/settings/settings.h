#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "settings/settings.h"

void settings_form(AsyncWebServer &server, JsonDocument &settingsDoc);