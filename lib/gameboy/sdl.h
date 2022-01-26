#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#ifndef SDL_H
#define SDL_H
int sdl_update(void);
void sdl_init(
    Adafruit_ILI9341 *sdl_screen_,
    int pin_up_,
    int pin_down_,
    int pin_right_,
    int pin_left_,
    int pin_a_,
    int pin_b_,
    int pin_select_,
    int pin_start_
);
void sdl_frame(void);
void sdl_quit(void);
byte* sdl_get_framebuffer(void);
unsigned int sdl_get_buttons(void);
unsigned int sdl_get_directions(void);
#endif
