#include "paint.h"

void Paint::begin() 
{
    gamepad->clearScreen();
    gamepad->setStatus("Paint");
}


void Paint::loop()
{
    if (gamepad->screenTouched())
    {
        ScreenPoint p = gamepad->getPoint();
        gamepad->screen->fillCircle(p.x, p.y, 3, ILI9341_WHITE);
    }
    delay(20);
}