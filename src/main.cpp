#include <Arduino.h>

#include <esp_wifi.h>
#include <esp_task_wdt.h>

#include "game-pad.h"
GamePad gamepad = GamePad();

#include "breakout.h"
Breakout breakout(&gamepad);

#include "paint.h"
Paint paint(&gamepad);

#include "reader.h"
Reader reader(&gamepad);

#include "gboy.h"
Gboy gboy(&gamepad);

#include "menu.h"
Menu menu(&gamepad);

void setup()
{
    
    // turn off WiFi
    //esp_wifi_deinit();
    
    // disable Core 0 WDT
    TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU(0);
    esp_task_wdt_delete(idle_0);


    menu.setItemsCount(4);
    menu.setItem(0, "Breakout", &breakout);
    menu.setItem(1, "Paint", &paint);
    menu.setItem(2, "Reader", &reader);
    menu.setItem(3, "GBoy", &gboy);

    gamepad.begin(&menu);
}

void loop()
{
    gamepad.loop();
}