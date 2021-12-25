//#define ENABLE_SD

#include <Arduino.h>
#include <StateMachine.h>

#ifdef ENABLE_SD
#include <SdFat.h>
#endif

#include "game-pad.h"
#include "breakout.h"

StateMachine machine = StateMachine();

GamePad gamepad = GamePad();

#ifdef ENABLE_SD
#define SPI_CLOCK SD_SCK_MHZ(50)
#define SD_CONFIG SdSpiConfig(SD_CS, SHARED_SPI, SPI_CLOCK)
SdFat sd;
#endif
bool SD_available = false;

//Breakout
Breakout breakout(&gamepad);
unsigned long lastFrame;
void loopGame()
{
  if (machine.executeOnce)
  {
    //Initialize
    lastFrame = millis();
    breakout.begin();
  }
  //Framerate limit
  while ((millis() - lastFrame) < 20)
    ;
  lastFrame = millis();

  breakout.loop();
}
State *stateGame = machine.addState(&loopGame);

//Paint
void loopPaint()
{
  if (machine.executeOnce)
  {
    gamepad.clearScreen();
    gamepad.setStatus("Paint");
  }
  if (gamepad.screenTouched())
  {
    ScreenPoint p = gamepad.getPoint();
    gamepad.screen->fillCircle(p.x, p.y, 3, ILI9341_WHITE);
  }
  delay(20);
}
State *statePaint = machine.addState(&loopPaint);

//Reader App
void loopReader()
{
  if (machine.executeOnce)
  {
    if (SD_available)
    {
#ifdef ENABLE_SD
      gamePad.setStatus("SD inserted");
      File myFile;
      myFile = sd.open("test2.txt", FILE_WRITE);
      // if the file opened okay, write to it:
      if (myFile)
      {
        gamePad.setStatus("Writing to test.txt...");
        myFile.println("testing 1, 2, 3.");
        // close the file:
        myFile.close();
        gamePad.setStatus("done writing.");
      }
      else
      {
        // if the file didn't open, print an error:
        gamePad.setStatus("error opening test.txt");
      }

      // re-open the file for reading:
      myFile = sd.open("test2.txt");
      if (myFile)
      {
        gamePad.setStatus("test.txt: reading..");

        // read from the file until there's nothing else in it:
        String w;
        while (myFile.available())
        {
          w = w + myFile.readString();
        }
        gamePad.setStatus("Done reading");
        tft.println(w);
        // close the file:
        myFile.close();
      }
      else
      {
        // if the file didn't open, print an error:
        gamePad.setStatus("error opening test.txt");
      }
#endif
    }
    else
    {
      gamepad.setStatus("SD unavailable");
    }
  }
}
State *stateReader = machine.addState(&loopReader);

void setup()
{
  gamepad.begin();
  gamepad.clearScreen();

//Initialize SD Card
#ifdef ENABLE_SD
  if (sd.begin(SD_CONFIG))
  {
    SD_available = true;
  }
  else
  {
    SD_available = false;
  }
#endif

  //machine.transitionTo(statePaint);
  machine.transitionTo(stateGame);
  //machine.transitionTo(stateReader);
}

void loop()
{
  machine.run();
}