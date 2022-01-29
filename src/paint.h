#ifndef PAINT_H
#define PAINT_H

#include "app.h"
#include "game-pad.h"

class Paint : public App
{
public:
    Paint(GamePad *gamepad) : App(gamepad) {};
    
    void begin();
    void loop();
private:
    int canvas_x;
    int canvas_y;
    GFXcanvas16* canvas;
    int pallet_x;
    int pallet_y;
    int pallet_cell_size;
    void drawPallet_();
    void drawCurrentColor_();
    int16_t colors[10];
    int16_t currentColor;
};

#endif