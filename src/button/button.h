#pragma once
#include <Arduino.h>

class Button{
    int pin;
public:
    Button(int pin);
    bool check();
};