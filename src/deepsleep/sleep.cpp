#include "deepsleep.h"

void sleep(){
    delay(500);
    esp_deep_sleep_start();
}