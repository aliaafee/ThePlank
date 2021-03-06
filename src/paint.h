#ifndef PAINT_H
#define PAINT_H

#include "app.h"
#include "game-pad.h"

class Paint : public App
{
public:
    Paint(GamePad *gamepad) : App(gamepad) {};
    String getName() { return "Paint"; }
    void begin();
    void loop();
};

#endif