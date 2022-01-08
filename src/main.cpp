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

#include "menu.h"
Menu menu(&gamepad);


void setup()
{
  menu.setItemsCount(3);
  menu.setItem(0, &breakout);
  menu.setItem(1, &paint);
  menu.setItem(2, &reader);

  gamepad.setHomeApp(&menu);
  gamepad.begin();
}

void loop()
{
  gamepad.loop();
}