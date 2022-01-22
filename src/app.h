#ifndef APP_H
#define APP_H

#include <Arduino.h>

class GamePad;

class App
{
public:
    GamePad *gamepad;
    App(GamePad *gamepad_) { gamepad = gamepad_; };
    
    virtual void begin() {};
    virtual void loop() {};
};


#endif