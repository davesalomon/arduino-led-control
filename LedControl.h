/*
  LedControl.h - Library for flashing Morse code.
  Created by Dave Salomon, September 2017.
  Released into the public domain.

  https://github.com/davesalomon/arduino-led-control
*/

#ifndef LedControl_h
#define LedControl_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

class LedControl
{
  public:
    LedControl(int, int);
    void initialize();
    uint32_t color(int, int, int);
    void fadeLedTo(int, uint32_t, int, int);
    void fadeLedsTo(int[], uint32_t, int, int);
    void fadeAllLedsTo(uint32_t, int, int);
    uint32_t randomColor();
    int selectRandomLed();
    void setLedColor(int, uint32_t);
    void setLedsColor(int[], uint32_t, int);
    void setAllLedsColor(uint32_t);
    void update();
    uint32_t Color_Red;
    uint32_t Color_Green;
    uint32_t Color_Blue;
    uint32_t Color_Yellow;
    uint32_t Color_Purple;
    uint32_t Color_Cyan;
    uint32_t Color_Off;
    uint32_t Color_White;
    uint32_t Color_Grey;
    int * evenLeds;
    int * oddLeds;
  private:
    Adafruit_NeoPixel strip;
    int ledCount;
};

#endif