#pragma once
#include "driver/gpio.h"
#include "settings.h"
#include <Arduino.h>

void sleep(int data, int clk, int cs);
void setWakeUp(int pin);
