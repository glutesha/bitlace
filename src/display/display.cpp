#include "display.h"

Display::Display(String color, int brightness, int clk, int data, int cs): 
    clk(clk), 
    data(data), 
    cs(cs), 
    color(color), 
    brightness(brightness),
    interface(U8G2_R0, clk, data, cs, U8X8_PIN_NONE, U8X8_PIN_NONE)
{
    interface.begin();
    interface.setFontMode(1);
    interface.setContrast(brightness*16);
    interface.setBitmapMode(1);
    interface.clearBuffer();
      
    bool defaultdrawing[8][8] = {{0, 0, 0, 0, 1, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 0, 0, 0},
                                 {0, 0, 1, 1, 1, 0, 0, 0},
                                 {0, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1, 0},
                                 {0, 0, 0, 1, 1, 1, 0, 0},
                                 {0, 0, 0, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 1, 0, 0, 0, 0}};

    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
           interface.setDrawColor(defaultdrawing[row][col]);
           interface.drawPixel(col, row);
           displaystate[row][col] = defaultdrawing[row][col];
        }
    }

    interface.sendBuffer();
}

void Display::setColor(String c){
    color = c;
}

String Display::getColor(){
    return color;
}

bool (&Display::getState())[8][8] {
    return displaystate;
}

void Display::drawArray(JsonArray display){
    for (int row = 0; row < 8; row++) {
        JsonArray rowArray = display[row].as<JsonArray>();
        for (int col = 0; col < 8; col++) {
          int color = rowArray[col] ? 1 : 0;
          interface.setDrawColor(color);
          interface.drawPixel(col, row);
          displaystate[row][col] = rowArray[col];
        }
      }
      interface.sendBuffer();
}