#include "game-pad.h"

GamePad::GamePad()
{
    screen = new Adafruit_ILI9341(SCREEN_CS, SCREEN_DC);
    touchScreen_ = new XPT2046_Touchscreen(TOUCH_CS, TOUCH_IRQ);
}

GamePad::~GamePad()
{
    ;
}

void GamePad::begin()
{
    pinMode(SCREEN_CS, OUTPUT);
    pinMode(SCREEN_DC, OUTPUT);
    pinMode(SCREEN_RESET, OUTPUT);

    digitalWrite(SCREEN_CS, HIGH);
    digitalWrite(SCREEN_DC, HIGH);
    digitalWrite(SCREEN_RESET, HIGH);

    pinMode(TOUCH_CS, OUTPUT);
    digitalWrite(TOUCH_CS, HIGH);

    screen->begin();
    screen->setRotation(3);

    touchScreen_->begin();
    touchScreen_->setRotation(30);

    sd_available_ = false;
#ifdef ENABLE_SD
    if (sd.begin(SD_CONFIG))
    {
        sd_available_ = true;
    }
    else
    {
        sd_available_ = false;
    }
#endif

    pinMode(BTN_UP, INPUT);
    pinMode(BTN_DOWN, INPUT);
    pinMode(BTN_RIGHT, INPUT);
    pinMode(BTN_LEFT, INPUT);
    pinMode(BTN_A, INPUT);
    pinMode(BTN_B, INPUT);
    pinMode(BTN_SELECT, INPUT);

    backgroundColor = ILI9341_BLACK;

    setCurrentApp(homeApp);
}

void GamePad::loop()
{
    if (currentApp == NULL) { return; }
    (currentApp)->loop();
}

void GamePad::setCurrentApp(App *app)
{
    app->begin();
    currentApp = app;
}

void GamePad::setHomeApp(App *app)
{
    homeApp = app;
}

void GamePad::gotoHomeApp()
{
    if (homeApp == NULL) { return; }

    setCurrentApp(homeApp);
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
        y - (h / 2)
    );

    screen->print(string);
}

void GamePad::beep()
{
    tone(BUZZER, 1000);
    delay(10);
    tone(BUZZER, 4000);
    delay(20);
    noTone(BUZZER);
}

bool GamePad::sd_available() {
    return sd_available_;
}