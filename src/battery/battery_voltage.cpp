#include "battery.h"

float read_battery_voltage(int pin){
    return 2 * analogReadMilliVolts(pin) / 1000;
}