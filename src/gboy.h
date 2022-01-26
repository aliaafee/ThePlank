#ifndef GBOY_H
#define GBOY_H

#include "app.h"
#include "game-pad.h"

#include "timer.h"
#include "rom.h"
#include "mem.h"
#include "cpu.h"
#include "lcd.h"
#include "sdl.h"


class Gboy : public App
{
public:
    Gboy(GamePad *gamepad) : App(gamepad) {};
    
    void begin();
    void loop();

    bool pressedUp() { return gamepad->pressedUp(); }
private:
    bool rom_loaded_;
    int frameTime;
};


#endif