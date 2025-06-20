#include "battery.h"

float read_battery_voltage(int pin, int resistance){

    float voltage = 2 * analogReadMilliVolts(pin);

    return voltage;
}