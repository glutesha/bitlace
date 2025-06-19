#include "server.h"

void enable_routes(AsyncWebServer &server, Display &current, JsonDocument settings){
  main(server);
  settings_form(server, settings);
  display_color(server, current);
  display_update(server, current);
  display_state(server, current);
}