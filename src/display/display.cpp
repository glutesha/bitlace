#include "display.h"
#include "driver/gpio.h"

Display::Display(String color, int brightness, int clk, int data, int cs,
                 bool flip)
    : color(color), brightness(brightness), clk(clk), data(data), cs(cs),
      cueState(1), cueCounter(1), shown(false), cueDelay(50), cueLastMillis(0), flip(flip),
      interface(U8G2_R0, clk, data, cs, U8X8_PIN_NONE, U8X8_PIN_NONE) {
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
  pinMode(clk, OUTPUT);
  digitalWrite(clk, LOW);
  pinMode(data, OUTPUT);
  digitalWrite(data, LOW);
  gpio_hold_dis((gpio_num_t)(clk));
  gpio_hold_dis((gpio_num_t)(data));
  gpio_hold_dis((gpio_num_t)(cs));
  gpio_deep_sleep_hold_dis();

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_UNDEFINED) {
    interface.initDisplay();
    interface.setContrast(brightness * 16);
  }
  shown = false;
  interface.setFontMode(1);
  interface.setBitmapMode(1);
  interface.clearBuffer();
}

void Display::setColor(String c) { color = c; }

String Display::getColor() { return color; }

bool (&Display::getState())[8][8] { return displaystate; }

void Display::powerSaveDraw() {
    interface.sendBuffer();
    if (!shown) {
        interface.setPowerSave(0);
        shown = true;
    }
}

void Display::powerSave() {
    interface.setPowerSave(1);
}

void Display::drawArray(JsonArray display) {
  if (flip) {
    for (int row = 7; row >= 0; row--) {
      JsonArray rowArray = display[7 - row].as<JsonArray>();
      JsonArray realrowArray = display[row].as<JsonArray>();
      for (int col = 7; col >= 0; col--) {
        int color = rowArray[7 - col] ? 1 : 0;
        interface.setDrawColor(color);
        interface.drawPixel(col, row);
        displaystate[row][col] = realrowArray[col];
      }
    }
  } else {
    for (int row = 0; row < 8; row++) {
      JsonArray rowArray = display[row].as<JsonArray>();
      for (int col = 0; col < 8; col++) {
        int color = rowArray[col] ? 1 : 0;
        interface.setDrawColor(color);
        interface.drawPixel(col, row);
        displaystate[row][col] = rowArray[col];
      }
    }
  }
  powerSaveDraw();
}

void Display::cue() {
  if ((millis() - cueLastMillis) > cueDelay) {
    cueLastMillis = millis();
    cueCounter += cueState;
    if (cueCounter == 10) {
      cueState = -1;
    }
    if (cueCounter == 1) {
      cueState = 1;
    }

    interface.setContrast(cueCounter * 16);
    powerSaveDraw();
  }
}

void Display::clear() {
  interface.clearBuffer();
  powerSaveDraw();
}

void Display::setBrightness(int setbrightness) {
  brightness = setbrightness;
  interface.setContrast(brightness * 16);
  powerSaveDraw();
}
