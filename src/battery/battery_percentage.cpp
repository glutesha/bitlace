#include "battery.h"

int read_battery_percentage(int pin){
    return map(read_battery_voltage(pin), 3.7, 4.2, 0, 100);
}