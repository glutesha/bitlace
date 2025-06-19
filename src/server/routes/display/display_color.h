#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#include "display/display.h"
void display_color(AsyncWebServer &server, Display &current);