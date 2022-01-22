#include "menu.h"

void Menu::begin() 
{
    currentItem = 0;
    gamepad->clearScreen();
    drawItems();
    highlightCurrentItem();
}

void Menu::loop()
{
    if (gamepad->pressedUp()) {
        selectPrev();
        delay(200);
    }
    
    if (gamepad->pressedDown() || gamepad->pressedSelect()) {
        selectNext();
        delay(200);
    }

    if (gamepad->pressedStart() || gamepad->pressedA()) {
        delay(200);
        gamepad->setCurrentApp(items[currentItem]);
    }
}

void Menu::setItem(int i, App* app) 
{
    if ( i > itemsCount - 1 ) { return ;}

    items[i] = app;
}


void Menu::drawItems()
{
    for (int i=0; i < itemsCount; i++) {
        gamepad->printCentered(320/2, (240/2) - 45 + (i * 30), items[i]->getName());
    }
}

void Menu::highlightCurrentItem()
{
    int x = 320/2;
    int y = (240/2) - 45 + (currentItem * 30);

    gamepad->screen->drawRect(
        x - 50, y - 15,
        100, 30,
        ILI9341_RED
    );
}

void Menu::unhighlightCurrentItem()
{
    int x = 320/2;
    int y = (240/2) - 45 + (currentItem * 30);

    gamepad->screen->drawRect(
        x - 50, y - 15,
        100, 30,
        gamepad->backgroundColor
    );
}

void Menu::selectNext()
{
    unhighlightCurrentItem();
    currentItem += 1;
    if (currentItem > itemsCount-1) { currentItem = 0;}
    highlightCurrentItem();
}

void Menu::selectPrev()
{
    unhighlightCurrentItem();
    currentItem -= 1;
    if (currentItem < 0) { currentItem = itemsCount-1;}
    highlightCurrentItem();
}