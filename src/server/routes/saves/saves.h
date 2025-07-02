#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#include "saves/saves.h"

void save(AsyncWebServer &server);
void remove(AsyncWebServer &server);
void get_saves(AsyncWebServer &server);