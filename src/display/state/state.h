#pragma once
#include <Arduino.h>
#include <LittleFS.h>

#include "display/display.h"
void load_state(Display &current);
void save_state(Display &current);