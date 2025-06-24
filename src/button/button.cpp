#include "button.h"

Button::Button(int pin): pin(pin), lastState(HIGH), debounce(40) {
    pinMode(pin, INPUT_PULLUP);
}

bool Button::read(){
    bool read = digitalRead(pin);
    if(read != lastState){
        lastDebounce = millis();
    }

    if((millis() - lastDebounce) > debounce){
        if(read != lastState){
            state = read;
        
            if(state){
                return state;
            }
        }
    }

    lastState = read;
    return false;
}

// https://docs.arduino.cc/built-in-examples/digital/Debounce