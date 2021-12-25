#include "game-pad.h"

GamePad::GamePad()
{
    screen = new Adafruit_ILI9341(screenCS_, screenDC_);
    touchScreen_ = new XPT2046_Touchscreen(touchScreenCS_, touchScreenIRQ_);
}

GamePad::~GamePad()
{
    ;
}

void GamePad::begin()
{
    pinMode(screenCS_, OUTPUT);
    pinMode(screenDC_, OUTPUT);
    pinMode(screenReset_, OUTPUT);

    digitalWrite(screenCS_, HIGH);
    digitalWrite(screenDC_, HIGH);
    digitalWrite(screenReset_, HIGH);

    pinMode(touchScreenCS_, OUTPUT);
    digitalWrite(touchScreenCS_, HIGH);

    screen->begin();
    screen->setRotation(3);

    touchScreen_->begin();
    touchScreen_->setRotation(30);

    pinMode(btnUpPin_, INPUT);
    pinMode(btnDownPin_, INPUT);
    pinMode(btnRightPin_, INPUT);
    pinMode(btnLeftPin_, INPUT);
    pinMode(btnAPin_, INPUT);
    pinMode(btnBPin_, INPUT);
    pinMode(btnBackPin_, INPUT);

    backgroundColor = ILI9341_BLACK;
}

bool GamePad::buttonPressed_(uint8_t btnPin)
{
    if (digitalRead(btnPin) == HIGH)
    {
        return true;
    }
    return false;
}

ScreenPoint GamePad::getPoint()
{
    TS_Point p = touchScreen_->getPoint();
    return {
        map(p.y, calYmin, calYmax, 320, 0),
        map(p.x, calXmin, calXmax, 240, 0)};
}

void GamePad::clearScreen()
{
    screen->fillScreen(backgroundColor);
}

void GamePad::setStatus(String status)
{
    screen->fillRect(0, 0, screen->width(), 22, backgroundColor);
    //tft.setFont(&FreeSans9pt7b);
    screen->setTextColor(ILI9341_WHITE);
    screen->setCursor(0, 9);
    screen->println(status);
}

void GamePad::printCentered(int16_t x, int16_t y, String string)
{
    int16_t x1, y1;
    uint16_t w, h;

    screen->getTextBounds(string, 0, 0, &x1, &y1, &w, &h);

    screen->setCursor(
        x - (w / 2),
        y - (h / 2)
    );

    screen->print(string);
}

void GamePad::beep()
{
    tone(buzzerPin_, 1000);
    delay(10);
    tone(buzzerPin_, 4000);
    delay(20);
    noTone(buzzerPin_);
}