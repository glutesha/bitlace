#pragma once
#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include "defines.h"

void save_settings(JsonDocument &settingsDoc);
void load_settings(JsonDocument &settingsDoc);