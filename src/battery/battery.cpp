#include "battery.h"

float read_battery_voltage(int pin, int resistance){
    int battery = 0;
    for(int i = 0; i < 16; i++) {
        battery = battery + analogReadMilliVolts(pin); // ADC with correction   
    } 
    float voltage = 2 * pin / 16 / resistance;

    return voltage;
}