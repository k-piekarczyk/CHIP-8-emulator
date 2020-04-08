#include <iostream>

#include "CHIP8.h"
#include "Graphics.h"
#include "Input.h"
#include "Beeper.h"
#include "Timer.h"

int main(int argc, char** argv) {

    CHIP8 chip;

    chip.initialize();

    Graphics g = Graphics(chip.getGFX());
    Input input = Input(chip.getKeys());

    Beeper beeper = Beeper();

    Timer soundTimer = Timer(*chip.getSoundTimerPtr(), &beeper);
    Timer delayTimer = Timer(*chip.getDelayTimerPtr());

    chip.loadRom("../roms/test.ch8");

    while (!input.isFinished()) {

            soundTimer.update();
            delayTimer.update();

            input.update();
            chip.next();
            g.draw();

    }

    return 0;
}
