#include "breakout.h"

Brick::Brick()
{
}

Brick::~Brick()
{
}

bool Brick::collided(Ball* ball)
{
    if (!visibile) {
        return false;
    }
    if (ball->x + ball->radius < x) {
        return false;
    }
    if (ball->x - ball->radius > x + width) {
        return false;
    }
    if (ball->y + ball->radius < y) {
        return false;
    }
    if (ball->y - ball->radius > y + height) {
        return false;
    }

    if (ball->x + ball->radius > x and ball->x - ball->radius < x + width) {
        if (ball->y > y) {
            ball->v_y = abs(ball->v_y);
        } else {
            ball->v_y = abs(ball->v_y) * -1;
        }
    } else {
        if (ball->x > x) {
            ball->v_x = abs(ball->v_x);
        } else {
            ball->v_x = abs(ball->v_x) * -1;
        }
    }

    return true;


    /*

    if (ball->x + ball->radius > x && ball->x - ball->radius < x + width ) {
        if (ball->y - ball->radius > y) {
            if (ball->y - ball->radius < y + height) {
                ball->v_y = abs(ball->v_y);
                return true;
            }
        }
        if (ball->y + ball->radius < y + height) {
            if (ball->y + ball->radius > y) {
                ball->v_y = abs(ball->v_y) * -1;
                return true;
            }
        }
    }

    if (ball->y + ball->radius > y && ball->y - ball->radius < y + height ) {
        if (ball->x - ball->radius > x) {
            if (ball->x - ball->radius < x + width) {
                ball->v_x = abs(ball->v_x);
                return true;
            }
        }
        if (ball->x + ball->radius < x + width) {
            if (ball->x + ball->radius > x) {
                ball->v_x = abs(ball->v_x) * -1;
                return true;
            }
        }
    }*/

    return false;

    /*
    float t_x = ball->x;
    float t_y = ball->y;
    if (t_x < x)
    {
        return false;
    }
    if (t_x > x + width)
    {
        return false;
    }
    if (t_y < y)
    {
        return false;
    }
    if (t_y > y + height)
    {
        return false;
    }
    return true;*/
}

void Brick::show(GamePad *gamepad)
{
    gamepad->screen->fillRect(x, y, width, height, ILI9341_WHITE);
    visibile = true;
}

void Brick::hide(GamePad *gamepad)
{
    gamepad->screen->fillRect(x, y, width, height, gamepad->backgroundColor);
    visibile = false;
}

Breakout::Breakout(GamePad *gamepad_)
{
    gamepad = gamepad_;
}

Breakout::~Breakout()
{
    ;
}

void Breakout::begin()
{
    lastFrame = millis();

    gamepad->setStatus("Breakout X");

    maxDeflection = 1.0472;

    paddle = {0, (float)gamepad->screen->width() / 2, 50, 5};

    ball = {
        (float)gamepad->screen->width() / 2,
        (float)gamepad->screen->height() / 2,
        (float)gamepad->screen->width() / 2,
        (float)gamepad->screen->height() / 2,
        0, 2,
        2,
        3};

    bounds = {
        ball.radius,
        ball.radius + 22,
        gamepad->screen->width() - ball.radius,
        gamepad->screen->height() - ball.radius - paddle.height};


    int brickColumns = 7;
    int brickRows = 6;
    brickCount = 42;
    int brickWidth = 300/brickColumns;

    for (int x = 0; x < brickColumns; x++) {
        for (int y = 0; y < brickRows; y++) {
            int i = y * brickColumns + x;
            bricks[i].x = x * brickWidth + 10;
            bricks[i].y = y * 10 + 20 + bounds.y_min;
            bricks[i].width = brickWidth - 2;
            bricks[i].height = 8;
        }
    }

    for (int i = 0; i < brickCount; i++)
    {
        bricks[i].show(gamepad);
    }

    currentLoop = &Breakout::playLoop;
}

void Breakout::loop()
{
    while ((millis() - lastFrame) < FRAME_TIME)
        ;
    lastFrame = millis();
    (this->*currentLoop)();
}

void Breakout::deadLoop()
{
    if (gamepad->pressedA())
    {
        restartGame();
    }
    return;
}

void Breakout::pauseLoop()
{
    if (gamepad->pressedA())
    {
        continueGame();
    }
    return;
}

void Breakout::playLoop()
{
    //Controls
    if (gamepad->pressedBack())
    {
        pauseGame();
    }
    if (gamepad->pressedRight())
    {
        if (paddle.x < bounds.x_max - paddle.width / 2)
        {
            paddle.x += 5;
        }
    }

    if (gamepad->pressedLeft())
    {
        if (paddle.x > bounds.x_min + paddle.width / 2)
        {
            paddle.x -= 5;
        }
    }

    //Motion
    ball.x += ball.v_x;
    ball.y += ball.v_y;

    //Collision Detection
    if (ball.x <= bounds.x_min)
    {
        ball.v_x = abs(ball.v_x);
        gamepad->beep();
    }
    if (ball.x >= bounds.x_max)
    {
        ball.v_x = abs(ball.v_x) * -1;
        gamepad->beep();
    }

    if (ball.y <= bounds.y_min)
    {
        ball.v_y = abs(ball.v_y);
        gamepad->beep();
    }
    if (ball.y >= bounds.y_max)
    {
        if (ball.x > paddle.x - paddle.width / 2 && ball.x < paddle.x + paddle.width / 2)
        {
            ball.v_y = abs(ball.v_y) * -1;
            float angle = ((ball.x - paddle.x) / (paddle.width / 2.0)) * maxDeflection;
            if (angle == 0)
            {
                ball.v_x = 0;
                ball.v_y = -1 * ball.speed;
            }
            else
            {
                ball.v_x = ball.speed * sin(angle);
                ball.v_y = ball.speed * cos(angle) * -1;
            }
            gamepad->beep();
        }
        else
        {
            gameOver();
        }
    }

    //Collision with Bricks
    for (int i = 0; i < brickCount; i++)
    {
        if (bricks[i].collided(&ball))
        {
            bricks[i].hide(gamepad);
            gamepad->beep();
        }
    }

    //Render
    if (ball.p_x != ball.x || ball.p_y != ball.y)
    {
        gamepad->screen->fillCircle(ball.p_x, ball.p_y, ball.radius, gamepad->backgroundColor);
        gamepad->screen->fillCircle(ball.x, ball.y, ball.radius, ILI9341_RED);
        ball.p_x = ball.x;
        ball.p_y = ball.y;
    }

    if (paddle.p_x != paddle.x)
    {
        gamepad->screen->fillRect(paddle.p_x - paddle.width / 2, gamepad->screen->height() - paddle.height, paddle.width, paddle.height, gamepad->backgroundColor);
        gamepad->screen->fillRect(paddle.x - paddle.width / 2, gamepad->screen->height() - paddle.height, paddle.width, paddle.height, ILI9341_BLUE);
        paddle.p_x = paddle.x;
    }
}

void Breakout::gameOver()
{
    currentLoop = &Breakout::deadLoop;
    gamepad->screen->fillRect(
        (bounds.x_max - bounds.x_min) / 2.0 - 60,
        (bounds.y_max - bounds.y_min) / 2.0 - 28,
        120,
        56,
        ILI9341_CYAN);

    gamepad->screen->setTextSize(2);
    gamepad->screen->setTextColor(ILI9341_RED);
    gamepad->printCentered(
        (bounds.x_max - bounds.x_min) / 2.0,
        (bounds.y_max - bounds.y_min) / 2.0 - 10,
        "Game Over");

    gamepad->screen->setTextSize(1);
    gamepad->screen->setTextColor(ILI9341_RED);
    gamepad->printCentered(
        (bounds.x_max - bounds.x_min) / 2.0,
        (bounds.y_max - bounds.y_min) / 2.0 + 10,
        "Press A to restart");
}

void Breakout::restartGame()
{
    gamepad->clearScreen();
    begin();
}

void Breakout::pauseGame()
{
    gamepad->setStatus("Breakout X: Paused, press A to continue, B to end.");
    currentLoop = &Breakout::pauseLoop;
}

void Breakout::continueGame()
{
    gamepad->setStatus("Breakout X");
    currentLoop = &Breakout::playLoop;
}