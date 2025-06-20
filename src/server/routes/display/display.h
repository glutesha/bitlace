#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#include "display/display.h"
#include "display/state/state.h"

void display_update(AsyncWebServer &server, Display &current);
void display_color(AsyncWebServer &server, Display &current);
void display_state(AsyncWebServer &server, Display &current);