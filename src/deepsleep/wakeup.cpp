#include "deepsleep.h"

void setWakeUp(int pin)
{
    esp_sleep_enable_timer_wakeup(5000000);
    esp_deep_sleep_enable_gpio_wakeup(BIT(pin), ESP_GPIO_WAKEUP_GPIO_LOW);
}
