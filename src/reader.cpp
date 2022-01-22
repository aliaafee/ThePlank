#include "reader.h"

void Reader::begin() 
{
    gamepad->clearScreen();
    gamepad->setStatus("Reader");

    if (!gamepad->sd_available()) {
        gamepad->setStatus("SD was not initalized");
        return;
    }

    gamepad->setStatus("SD available");
    File myFile;
    myFile = gamepad->sd->open("test3.txt", FILE_WRITE);
    // if the file opened okay, write to it:
    if (myFile)
    {
        gamepad->setStatus("Writing to test.txt...");
        myFile.println("testing 1, 2, 3.");
        // close the file:
        myFile.close();
        gamepad->setStatus("done writing.");
    }
    else
    {
        // if the file didn't open, print an error:
        gamepad->setStatus("error opening test.txt");
    }

    // re-open the file for reading:
    myFile = gamepad->sd->open("test3.txt");
    if (myFile)
    {
        gamepad->setStatus("test.txt: reading..");

        // read from the file until there's nothing else in it:
        String w;
        while (myFile.available())
        {
        w = w + myFile.readString();
        }
        gamepad->setStatus("Done reading");
        gamepad->screen->println(w);
        // close the file:
        myFile.close();
    }
    else
    {
      // if the file didn't open, print an error:
      gamepad->setStatus("error opening test.txt");
    }
}


void Reader::loop()
{
    ;
}