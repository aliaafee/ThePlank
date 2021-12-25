#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
//#include <Fonts/FreeSans9pt7b.h>
#include <XPT2046_Touchscreen.h>

#ifndef GAME_PAD_H
#define GAME_PAD_H

#define screenCS_ A5
#define screenDC_ A3
#define screenReset_ A4
#define touchScreenCS_ A2
#define touchScreenIRQ_ 2
#define btnUpPin_ 8
#define btnDownPin_ 7
#define btnRightPin_ 6
#define btnLeftPin_ 9
#define btnAPin_ 4
#define btnBPin_ 5
#define btnBackPin_ A0
#define buzzerPin_ 3

#define calXmin 177
#define calXmax 3860
#define calYmin 93
#define calYmax 3737

struct ScreenPoint
{
  long x;
  long y;
};

class GamePad
{
public:
  Adafruit_ILI9341 *screen;
  int16_t backgroundColor;

  GamePad();
  ~GamePad();

  void begin();

  bool pressedUp() { return buttonPressed_(btnUpPin_); }
  bool pressedDown() { return buttonPressed_(btnDownPin_); }
  bool pressedRight() { return buttonPressed_(btnRightPin_); }
  bool pressedLeft() { return buttonPressed_(btnLeftPin_); }
  bool pressedA() { return buttonPressed_(btnAPin_); }
  bool pressedB() { return buttonPressed_(btnBPin_); }
  bool pressedBack() { return buttonPressed_(btnBackPin_); }

  bool screenTouched() { return touchScreen_->tirqTouched(); }
  ScreenPoint getPoint();

  void clearScreen();
  void setStatus(String status);
  void printCentered(int16_t x, int16_t y, String text);

  void beep();

private:
  XPT2046_Touchscreen *touchScreen_;

  bool buttonPressed_(uint8_t btnPin);
};

#endif