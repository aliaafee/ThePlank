#ifndef MENU_H
#define MENU_H

#include "app.h"
#include "game-pad.h"



class Menu : public App
{
public:
    
    Menu(GamePad *gamepad) : App(gamepad) { itemsCount = 4; };
    void begin();
    void loop();

    void setItemsCount(int count) { itemsCount = count; }
    void setItem(int i, String name, App* app);
private:
    App *items[4];
    String names[4];
    int itemsCount;
    void drawItems();
    void highlightCurrentItem();
    void unhighlightCurrentItem();
    void selectNext();
    void selectPrev();
    int currentItem;
};


#endif