#ifndef READER_H
#define READER_H

#include "app.h"
#include "game-pad.h"

class Reader : public App
{
public:
    Reader(GamePad *gamepad) : App(gamepad) {};

    String getName() { return "Reader"; }
    void begin();
    void loop();
};

#endif