#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "app.h"
#include "game-pad.h"

#define FRAME_TIME 20

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


class Brick
{
public:
    Brick();
    ~Brick();

    bool collided(Ball* ball);
    void show(GamePad *gamepad);
    void hide(GamePad *gamepad);

    float x;
    float y;
    float width;
    float height;
    bool visibile;
};


class Breakout : public App
{
public:
    //GamePad *gamepad;
    Breakout(GamePad *gamepad_) : App(gamepad_) {};
    ~Breakout() {};

    String getName() { return "Breakout"; }
    void begin();
    void loop();

private:
    unsigned long lastFrame;
    Ball ball;
    Paddle paddle;
    Bounds bounds;
    Brick bricks[42];
    int brickCount;

    float maxDeflection;

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