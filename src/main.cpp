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
  menu.setItem(0, "Breakout", &breakout);
  menu.setItem(1, "Paint", &paint);
  menu.setItem(2, "Reader", &reader);

  gamepad.begin(&menu);
}

void loop()
{
  gamepad.loop();
}