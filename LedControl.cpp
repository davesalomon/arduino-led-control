/*
  LedControl.h - Library for flashing Morse code.
  Created by Dave Salomon, September 2017.
  Released into the public domain.

  https://github.com/davesalomon/arduino-led-control
*/

#include <LedControl.h>
#include <Adafruit_NeoPixel.h>
#include <time.h>
#include <stdlib.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

LedControl::LedControl(int dataPin, int ledCount)
{
  this->ledCount = ledCount;
  this->strip = Adafruit_NeoPixel(ledCount, dataPin, NEO_GRB + NEO_KHZ800);
  this->Color_Red = this->strip.Color(255, 0, 0);
  this->Color_Green = this->strip.Color(0, 255, 0);
  this->Color_Blue = this->strip.Color(0, 0, 255);
  this->Color_Yellow = this->strip.Color(255, 255, 0);
  this->Color_Purple = this->strip.Color(255, 0, 255);
  this->Color_Cyan = this->strip.Color(0, 255, 255);
  this->Color_Off = this->strip.Color(0, 0, 0);
  this->Color_White = this->strip.Color(255, 255, 255);
  this->Color_Grey = this->strip.Color(127, 127, 127);
  srand(time(NULL));
}

void LedControl::initialize() {
  this->strip.begin();
  this->strip.show();
}

void LedControl::setLedColor(int ledNumber, uint32_t color)
{
  this->strip.setPixelColor(ledNumber, color);
}

void LedControl::setLedsColor(int ledNumbers[], uint32_t color, int arraySize)
{
  for(int i = 0; i < arraySize; ++i) {
    this->setLedColor(ledNumbers[i], color);
  }
}

void LedControl::setAllLedsColor(uint32_t color) {
  for(int i = 0; i < this->ledCount; ++i) {
    this->setLedColor(i+1, color);
  }
}

void LedControl::fadeLedTo(int ledNumber, uint32_t targetColor, int stepDelay) {
  uint32_t currentColor = this->strip.getPixelColor(ledNumber);
  int currentColorBlue = currentColor & 0xFF; 
  int currentColorGreen = (currentColor >> 8) & 0xFF; 
  int currentColorRed = (currentColor >> 16) & 0xFF;  
  int targetColorBlue = targetColor & 0xFF; 
  int targetColorGreen = (targetColor >> 8) & 0xFF; 
  int targetColorRed = (targetColor >> 16) & 0xFF;   

  while ((currentColorRed != targetColorRed) || (currentColorGreen != targetColorGreen) || (currentColorBlue != targetColorBlue)){
    if (currentColorRed < targetColorRed) currentColorRed++; else if (currentColorRed > targetColorRed) currentColorRed--;
    if (currentColorGreen < targetColorGreen) currentColorGreen++; else if (currentColorGreen > targetColorGreen) currentColorGreen--;
    if (currentColorBlue < targetColorBlue) currentColorBlue++; else if (currentColorBlue > targetColorBlue) currentColorBlue--;
    this->strip.setPixelColor(ledNumber, this->strip.Color(currentColorRed, currentColorGreen, currentColorBlue));
    delay(stepDelay);
    this->strip.show();
  }
}

void LedControl::fadeLedsTo(int ledNumbers[], uint32_t targetColor, int stepDelay, int arraySize) {
  for(int i = 0; i < arraySize; ++i) {
    uint32_t currentColor = this->strip.getPixelColor(ledNumbers[i]);
    int currentColorBlue = currentColor & 0xFF; 
    int currentColorGreen = (currentColor >> 8) & 0xFF; 
    int currentColorRed = (currentColor >> 16) & 0xFF;  
    int targetColorBlue = targetColor & 0xFF; 
    int targetColorGreen = (targetColor >> 8) & 0xFF; 
    int targetColorRed = (targetColor >> 16) & 0xFF;   

    bool allColorsCorrect = true;
    if ((currentColorRed != targetColorRed) || (currentColorGreen != targetColorGreen) || (currentColorBlue != targetColorBlue)){
      allColorsCorrect = false;
      if (currentColorRed < targetColorRed) currentColorRed++; else if (currentColorRed > targetColorRed) currentColorRed--;
      if (currentColorGreen < targetColorGreen) currentColorGreen++; else if (currentColorGreen > targetColorGreen) currentColorGreen--;
      if (currentColorBlue < targetColorBlue) currentColorBlue++; else if (currentColorBlue > targetColorBlue) currentColorBlue--;
      this->strip.setPixelColor(ledNumbers[i], this->strip.Color(currentColorRed, currentColorGreen, currentColorBlue));
      this->strip.show();
      delay(stepDelay);
      this->fadeLedsTo(ledNumbers, targetColor, stepDelay, arraySize);
    }
  }
}

void LedControl::fadeAllLedsTo(uint32_t targetColor, int stepDelay) {
  int targetColorBlue = targetColor & 0xFF; 
  int targetColorGreen = (targetColor >> 8) & 0xFF; 
  int targetColorRed = (targetColor >> 16) & 0xFF;   

  bool allColorsCorrect = true;
  for(int i = 0; i < this->ledCount; ++i) {
    uint32_t currentColor = this->strip.getPixelColor(i);
    int currentColorBlue = currentColor & 0xFF; 
    int currentColorGreen = (currentColor >> 8) & 0xFF; 
    int currentColorRed = (currentColor >> 16) & 0xFF;  

    if ((currentColorRed != targetColorRed) || (currentColorGreen != targetColorGreen) || (currentColorBlue != targetColorBlue)){
      allColorsCorrect = false;
      if (currentColorRed < targetColorRed) currentColorRed++; else if (currentColorRed > targetColorRed) currentColorRed--;
      if (currentColorGreen < targetColorGreen) currentColorGreen++; else if (currentColorGreen > targetColorGreen) currentColorGreen--;
      if (currentColorBlue < targetColorBlue) currentColorBlue++; else if (currentColorBlue > targetColorBlue) currentColorBlue--;
      this->setLedColor(i, this->strip.Color(currentColorRed, currentColorGreen, currentColorBlue));
    }
  }
  
  this->strip.show();
  if(!allColorsCorrect) {
    delay(stepDelay);
    this->fadeAllLedsTo(targetColor, stepDelay);
  }
}

void LedControl::update()
{
  this->strip.show();
}

uint32_t LedControl::randomColor() {
  return this->strip.Color(rand() % 255, rand() % 255, rand() % 255);
}
