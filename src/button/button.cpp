#include "button.h"

Button::Button(int pin): pin(pin), state(HIGH), lastState(HIGH), debounce(60), lastDebounce(0) {
    pinMode(pin, INPUT_PULLUP);
}

bool Button::read(){
    bool read = digitalRead(pin);
    if(read != lastState){
        lastDebounce = millis();
    }

    if((millis() - lastDebounce) > debounce){
        if(read != state){
            state = read;
        }
    }

    lastState = read;
    return !state;
}

// https://docs.arduino.cc/built-in-examples/digital/Debounce
