#include "gboy.h"

void Gboy::begin() 
{
    rom_loaded_ = false;

    gamepad->clearScreen();
    gamepad->setStatus("GBoy");

    File root = gamepad->sd->open("/");
    if (!root) {
        gamepad->screen->println("SD could not be opened");
        return;
    }

    gamepad->screen->print("Looking for GB ROM... ");
    File currentFile = root.openNextFile();
    File romfile;
    while (currentFile)
    {
        if (!currentFile.isDirectory()) {
            String filename = gamepad->getFileName(currentFile);
            if (filename.endsWith(".gb")) {
                romfile = currentFile;
                gamepad->screen->print("Found ROM: ");
                gamepad->screen->println(filename);
            }
        }
        currentFile = root.openNextFile();
    }

    gamepad->screen->println("Loading ROM...");
    
    if (!romfile) {
        gamepad->screen->println("Failed to open ROM file.");
        return;
    }
  
	size_t romsize = romfile.size();
    gamepad->screen->print("Size: ");
    gamepad->screen->println(romsize);

    unsigned char* gb_rom_loaded = (unsigned char*)calloc(romsize, 1);
	if (!gb_rom_loaded) {
        gamepad->screen->println("Could not alloct memory for ROM.");
        return;
    }

    romfile.read(gb_rom_loaded, romsize);

    gamepad->screen->println("ROM Load Succesful.");

    rom_init(gb_rom_loaded);
    sdl_init(
        gamepad->screen,
        BTN_UP,
        BTN_DOWN,
        BTN_RIGHT,
        BTN_LEFT,
        BTN_A,
        BTN_B,
        BTN_SELECT,
        BTN_START
    );
    mem_init2();
    cpu_init();

    gamepad->clearScreen();
    gamepad->setStatus("GBoy");

    rom_loaded_ = true;
}


void Gboy::loop()
{
    if (!rom_loaded_) {
        return;
    }

    //frameTime = micros();

    cpu_cycle();
    lcd_cycle();
    //timer_cycle();

    //gamepad->setStatus((String) (micros() - frameTime));
}