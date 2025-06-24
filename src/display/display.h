#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include <ArduinoJson.h>

class Display{
  private:
    String color;
    int brightness;
    int currentBrightness;
    int clk;
    int data;
    int cs;
    bool displaystate[8][8];
    U8G2_MAX7219_8X8_F_4W_SW_SPI interface;
  public:
    Display(String color, int brightness, int clk, int data, int cs);
    void setColor(String c);
    String getColor();
    bool (&getState())[8][8];
    void drawArray(JsonArray display);
    void cue();
};