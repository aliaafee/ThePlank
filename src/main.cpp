#include <Arduino.h>

//#define ENABLE_SD
#include "game-pad.h"

GamePad gamepad = GamePad();

#include "breakout.h"
Breakout breakout(&gamepad);

#include "paint.h"
Paint paint(&gamepad);

#include "reader.h"
Reader reader(&gamepad);


void setup()
{
  gamepad.setHomeApp(&breakout);
  gamepad.begin();
}

void loop()
{
  gamepad.loop();
}