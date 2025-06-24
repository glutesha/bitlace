#pragma once
#include <Arduino.h>

class Button{
    int pin;
    bool state;
    bool lastState;
    unsigned long debounce;
    unsigned long last_debounce;
public:
    Button(int pin);
    bool check();
};