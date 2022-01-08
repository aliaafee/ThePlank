//#define ENABLE_SD

#include <Arduino.h>

#ifdef ENABLE_SD
#include <SdFat.h>
#endif

#include "game-pad.h"
#include "breakout.h"

GamePad gamepad = GamePad();

//Breakout
Breakout breakout(&gamepad);
//unsigned long lastFrame;
void beginGame()
{
  breakout.begin();
}
void loopGame()
{
  breakout.loop();
}

//Paint
void beginPaint()
{
  gamepad.clearScreen();
  gamepad.setStatus("Paint");
}
void loopPaint()
{
  if (gamepad.screenTouched())
  {
    ScreenPoint p = gamepad.getPoint();
    gamepad.screen->fillCircle(p.x, p.y, 3, ILI9341_WHITE);
  }
  delay(20);
}

//Reader App
void beginReader()
{
  if (gamepad.sd_available())
  {
#ifdef ENABLE_SD
    gamepad.setStatus("SD inserted");
    File myFile;
    myFile = gamepad.sd.open("test2.txt", FILE_WRITE);
    // if the file opened okay, write to it:
    if (myFile)
    {
      gamepad.setStatus("Writing to test.txt...");
      myFile.println("testing 1, 2, 3.");
      // close the file:
      myFile.close();
      gamepad.setStatus("done writing.");
    }
    else
    {
      // if the file didn't open, print an error:
      gamepad.setStatus("error opening test.txt");
    }

    // re-open the file for reading:
    myFile = gamepad.sd.open("test2.txt");
    if (myFile)
    {
      gamepad.setStatus("test.txt: reading..");

      // read from the file until there's nothing else in it:
      String w;
      while (myFile.available())
      {
        w = w + myFile.readString();
      }
      gamepad.setStatus("Done reading");
      gamepad.screen->println(w);
      // close the file:
      myFile.close();
    }
    else
    {
      // if the file didn't open, print an error:
      gamepad.setStatus("error opening test.txt");
    } 
#endif
  }
  else
  {
    gamepad.setStatus("SD unavailable");
  }
  
}
void loopReader()
{

}


void setup()
{
  gamepad.begin();
  gamepad.clearScreen();

  beginGame();
  //beginReader();
}

void loop()
{
  loopGame();
  //loopReader();
}