#pragma once
#include <Arduino.h>

class Button{
    int pin;
    bool state;
    bool lastState;
    unsigned long debounce;
    unsigned long lastDebounce;
public:
    Button(int pin);
    bool read();
};