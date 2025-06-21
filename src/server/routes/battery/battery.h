#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <Battery.h>

void battery(AsyncWebServer &server, Battery &power);
