#ifndef GAME_PAD_H
#define GAME_PAD_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Fonts/FreeSans9pt7b.h>
#include <XPT2046_Touchscreen.h>

#include "pin-config.h"
#include "app.h"

#define calXmin 177
#define calXmax 3860
#define calYmin 93
#define calYmax 3737

#include <SdFat.h>
#define SPI_CLOCK SD_SCK_MHZ(16)
#define SD_CONFIG SdSpiConfig(SD_CS, SHARED_SPI, SPI_CLOCK)

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

    void begin(App *app);
    void loop();
    void setCurrentApp(App *app);
    void gotoHomeApp();

    bool pressedUp() { return buttonPressed_(BTN_UP); }
    bool pressedDown() { return buttonPressed_(BTN_DOWN); }
    bool pressedRight() { return buttonPressed_(BTN_RIGHT); }
    bool pressedLeft() { return buttonPressed_(BTN_LEFT); }
    bool pressedA() { return buttonPressed_(BTN_A); }
    bool pressedB() { return buttonPressed_(BTN_B); }
    bool pressedSelect() { return buttonPressed_(BTN_SELECT); }
    bool pressedStart() { return buttonPressed_(BTN_START); }

    bool screenTouched() { return touchScreen_->tirqTouched(); }
    ScreenPoint getPoint();

    void clearScreen();
    void setStatus(String status);
    void printCentered(int16_t x, int16_t y, String text);

    void beep();

    bool sd_available();

    SdFat *sd;

    String getFileName(File &file_);

private:
    XPT2046_Touchscreen *touchScreen_;
    bool buttonPressed_(uint8_t btnPin);
    bool sd_available_;
    App *homeApp;
    App *currentApp;
};

#endif