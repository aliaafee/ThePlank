#include "sdl.h"

Adafruit_ILI9341 *sdl_screen;
int pin_up;
int pin_down;
int pin_right;
int pin_left;
int pin_a;
int pin_b;
int pin_select;
int pin_start;

void backlighting(bool state)
{
  /*
    if (!state) {
        digitalWrite(_led, LOW);
    }
    else {
        digitalWrite(_led, HIGH);
    }*/
}

#define GAMEBOY_HEIGHT 160
#define GAMEBOY_WIDTH 144
byte pixels[GAMEBOY_HEIGHT * GAMEBOY_WIDTH / 4];
uint16_t bitmap[GAMEBOY_WIDTH * GAMEBOY_HEIGHT];

volatile bool frameUpdate;
TaskHandle_t screenUpdater;

static int button_start, button_select, button_a, button_b, button_down, button_up, button_left, button_right;

byte getColorIndexFromFrameBuffer(int x, int y)
{
  int offset = x + y * 160;
  byte value = (pixels[offset >> 2] >> ((offset & 3) << 1)) & 3;
  return value;
}
//const int color[] = {0x000000, 0x555555, 0xAAAAAA, 0xFFFFFF};
const int color[] = {0xFFFFFF, 0xAAAAAA, 0x555555, 0x000000};

void screenUpdateFunction(void *paremeter)
{
  while (true)
  {
    if (frameUpdate)
    {
      int i, j;
      for (i = 0; i < GAMEBOY_WIDTH; i = i + 1)
      {
        for (j = 0; j < GAMEBOY_HEIGHT; j = j + 1)
        {
          bitmap[j + i * GAMEBOY_HEIGHT] = color[getColorIndexFromFrameBuffer(j, i)];
        }
      }
      sdl_screen->drawRGBBitmap(80, 50, bitmap, GAMEBOY_HEIGHT, GAMEBOY_WIDTH);
      frameUpdate = false;
    }
  }
}

void sdl_init(
    Adafruit_ILI9341 *sdl_screen_,
    int pin_up_,
    int pin_down_,
    int pin_right_,
    int pin_left_,
    int pin_a_,
    int pin_b_,
    int pin_select_,
    int pin_start_)
{
  pin_up = pin_up_;
  pin_down = pin_down_;
  pin_right = pin_right_;
  pin_left = pin_left_;
  pin_a = pin_a_;
  pin_b = pin_b_;
  pin_select = pin_select_;
  pin_start = pin_start_;

  sdl_screen = sdl_screen_;
  sdl_screen->println("Core 0 init...");
  xTaskCreatePinnedToCore(
      screenUpdateFunction,
      "ScreenUpDateTask",
      1000,
      NULL,
      0,
      &screenUpdater,
      0);
}

bool buttonPressed_(uint8_t btnPin)
{
  if (digitalRead(btnPin) == LOW)
  {
    return true;
  }
  return false;
}

int sdl_update(void)
{

  return 0;
}
unsigned int sdl_get_buttons(void)
{
  button_select = buttonPressed_(pin_select);
  button_start = buttonPressed_(pin_start);
  button_a = buttonPressed_(pin_a);
  button_b = buttonPressed_(pin_b);
  return (button_start * 8) | (button_select * 4) | (button_b * 2) | button_a;
}

unsigned int sdl_get_directions(void)
{
  button_up = buttonPressed_(pin_up);
  button_down = buttonPressed_(pin_down);
  button_left = buttonPressed_(pin_left);
  button_right = buttonPressed_(pin_right);
  return (button_down * 8) | (button_up * 4) | (button_left * 2) | button_right;
}

byte *sdl_get_framebuffer(void)
{
  return pixels;
}

void sdl_frame(void)
{
  frameUpdate = true;
}
