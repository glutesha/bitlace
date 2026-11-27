#include "deepsleep.h"

void sleep(int data, int clk, int cs)
{
    gpio_hold_en((gpio_num_t)(data));
    gpio_hold_en((gpio_num_t)(clk));
    gpio_hold_en((gpio_num_t)(cs));
    gpio_deep_sleep_hold_en();
    delay(800);
    esp_deep_sleep_start();
}
