#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include <ArduinoJson.h>

class Display{
  private:
    String color;
    int brightness;
    int clk;
    int data;
    int cs;
    int cueState;
    int cueCounter;
    unsigned long cueDelay;
    unsigned long cueLastMillis;
    bool displaystate[8][8];
    bool flip;
    U8G2_MAX7219_8X8_F_4W_SW_SPI interface;
  public:
    Display(String, int, int, int, int, bool);
    void setColor(String);
    String getColor();
    bool (&getState())[8][8];
    void drawArray(JsonArray);
    void setBrightness(int);
    void cue();
    void clear();
};