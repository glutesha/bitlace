#pragma once
#include <ESPAsyncWebServer.h>

#include "display/display.h"
#include "display/state/state.h"

void display_state(AsyncWebServer &server, Display &current);