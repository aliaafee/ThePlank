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

    if (gamepad->pressedA()) { gamepad->setStatus("A");}
    if (gamepad->pressedB()) { gamepad->setStatus("B");}
    if (gamepad->pressedUp()) { gamepad->setStatus("Up");}
    if (gamepad->pressedDown()) { gamepad->setStatus("Down");}
    if (gamepad->pressedRight()) { gamepad->setStatus("Right");}
    if (gamepad->pressedLeft()) { gamepad->setStatus("Left");}

    delay(20);
}