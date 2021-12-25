#include "game-pad.h"

#ifndef BREAKOUT_H
#define BREAKOUT_H

struct Ball
{
    float p_x;
    float p_y;
    float x;
    float y;
    float v_x;
    float v_y;
    float speed;
    float radius;
};

struct Paddle
{
    float p_x;
    float x;
    float width;
    float height;
};

struct Bounds
{
    float x_min;
    float y_min;
    float x_max;
    float y_max;
};



class Breakout
{
public:
    GamePad *gamepad;
    Breakout(GamePad *gamepad_);
    ~Breakout();

    void begin();
    void loop();

private:
    Ball ball;
    Paddle paddle;
    Bounds bounds;
    float maxDeflection;
    bool alive;
    bool paused;

    void gameOver();
    void restartGame();
    void pauseGame();
    void continueGame();

    void (Breakout::*currentLoop)();
    void playLoop();
    void deadLoop();
    void pauseLoop();
};

#endif