#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

void push_saves(AsyncWebServer &server);
void load_saves(AsyncWebServer &server);