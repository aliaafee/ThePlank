#include "game-pad.h"

GamePad::GamePad()
{
    screen = new Adafruit_ILI9341(SCREEN_CS, SCREEN_DC, SCREEN_RESET);
    touchScreen_ = new XPT2046_Touchscreen(TOUCH_CS, TOUCH_IRQ);
    sd = new SdFat();
}

GamePad::~GamePad()
{
    ;
}

void GamePad::begin(App *app)
{
    pinMode(TOUCH_CS, OUTPUT);
    digitalWrite(TOUCH_CS, HIGH);

    screen->begin();
    screen->setRotation(3);

    touchScreen_->begin();
    touchScreen_->setRotation(30);

    sd_available_ = false;

    if (sd->begin(SD_CONFIG))
    {
        sd_available_ = true;
    }
    else
    {
        sd_available_ = false;
    }

    pinMode(BTN_SELECT, INPUT_PULLUP);
    pinMode(BTN_START, INPUT_PULLUP);
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);
    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_B, INPUT_PULLUP);
    pinMode(BTN_A, INPUT_PULLUP);

    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);

    backgroundColor = ILI9341_BLACK;

    homeApp = app;
    setCurrentApp(app);
}

void GamePad::loop()
{
    if (currentApp == NULL)
    {
        return;
    }
    (currentApp)->loop();
}

void GamePad::setCurrentApp(App *app)
{
    app->begin();
    currentApp = app;
}

void GamePad::gotoHomeApp()
{
    if (homeApp == NULL)
    {
        return;
    }

    setCurrentApp(homeApp);
}

bool GamePad::buttonPressed_(uint8_t btnPin)
{
    if (digitalRead(btnPin) == LOW)
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
    //screen->setFont(&FreeSans9pt7b);
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
        y - (h / 2));

    screen->print(string);
}

void GamePad::beep()
{
    ledcAttachPin(BUZZER, 0);
    ledcWriteNote(BUZZER, NOTE_Bb, 4);
    delay(50);
    ledcDetachPin(BUZZER);
}

bool GamePad::sd_available()
{
    return sd_available_;
}