#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "display/display.h"

#include "server/routes/app/app.h"
#include "server/routes/display/display_state.h"
#include "server/routes/display/display_update.h"
#include "server/routes/display/display_color.h"
#include "server/routes/settings/settings.h"

void enable_routes(AsyncWebServer &server, Display &current, JsonDocument &settings);