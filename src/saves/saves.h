#pragma once
#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

JsonDocument load_saves(){}
String save(JsonDocument, int){}
String remove(int){}