#pragma once
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "display/display.h"

#include "server/routes/main/main.h"
#include "server/routes/display/display_state.h"
#include "server/routes/display/display_update.h"
#include "server/routes/display/display_color.h"
#include "server/routes/settings/settings.h"

void enable_routes(Display &current, JsonDocument settings);