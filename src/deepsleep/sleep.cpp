#include "deepsleep.h"

void sleep(){
    delay(100);
    esp_deep_sleep_start();
}