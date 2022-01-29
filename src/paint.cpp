#include "paint.h"

void Paint::begin()
{
    gamepad->clearScreen();

    canvas = new GFXcanvas16(235, 235);
    canvas->fillScreen(ILI9341_WHITE);
    canvas_x = 10;
    canvas_y = 2;

    pallet_x = (canvas->width() + canvas_x + 5);
    pallet_y = canvas_y;
    pallet_cell_size = 32;

    colors[0] = ILI9341_WHITE;
    colors[1] = ILI9341_RED;
    colors[2] = ILI9341_GREEN;
    colors[3] = ILI9341_BLUE;
    colors[4] = ILI9341_BLACK;
    colors[5] = ILI9341_MAROON;
    colors[6] = ILI9341_PURPLE;
    colors[7] = ILI9341_DARKGREY;
    colors[8] = ILI9341_YELLOW;
    colors[9] = ILI9341_PINK;

    currentColor = ILI9341_BLACK;

    drawPallet_();
    drawCurrentColor_();
    gamepad->screen->drawRGBBitmap(canvas_x, canvas_y, canvas->getBuffer(), canvas->width(), canvas->height());
}

void Paint::loop()
{
    if (gamepad->screenTouched())
    {
        ScreenPoint p = gamepad->getPoint();
        if (p.x > pallet_x && p.y > pallet_y)
        {
            int x = (p.x - pallet_x) / pallet_cell_size;
            int y = (p.y - pallet_y) / pallet_cell_size;
            if (x > 1) {
                return;
            }
            if (y > 4) {
                return;
            }
            int i = x + y * 2;
            currentColor = colors[i];
            drawCurrentColor_();
        }
        else
        {
            canvas->fillCircle(p.x - canvas_x, p.y - canvas_y, 3, currentColor);
            gamepad->screen->drawRGBBitmap(canvas_x, canvas_y, canvas->getBuffer(), canvas->width(), canvas->height());
        }
    }
}

void Paint::drawPallet_()
{
    for (int x = 0; x < 2; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            int i = x + y * 2;
            gamepad->screen->fillRect(pallet_x + x * pallet_cell_size, pallet_y + y * pallet_cell_size, pallet_cell_size, pallet_cell_size, colors[i]);
        }
    }
}

void Paint::drawCurrentColor_()
{
    gamepad->screen->fillRect(
        (canvas->width() + canvas_x + 5), canvas_y + 10 + 5 * 32,
        32 * 2, 32 * 2,
        ILI9341_WHITE);

    gamepad->screen->fillRect(
        (canvas->width() + canvas_x + 5) + 5, canvas_y + 15 + 5 * 32,
        32 * 2 - 10, 32 * 2 - 10,
        currentColor);
}