#include <iostream>
#include "CHIP8.hpp"
#include "Display.hpp"
#include "Input.hpp"
#include "Beeper.hpp"
#include "Timer.hpp"

int main(int argc, char **argv) {
    CHIP8 chip;

    chip.initialize();

    Display g = Display(chip.getGFX());
    Input input = Input(chip.getKeys());

    Beeper beeper = Beeper();
    Timer soundTimer = Timer(*chip.getSoundTimerPtr(), &beeper);
    Timer delayTimer = Timer(*chip.getDelayTimerPtr());

    chip.loadRom("../roms/slipperyslope.ch8");

    chip.loadInputHandler(&input);

    while (!input.isFinished()) {

        for(int i=0;i<30;i++) {
            soundTimer.update();
            delayTimer.update();

            input.update();
            chip.next();
            g.draw();
        }
    }

    return 0;
}



