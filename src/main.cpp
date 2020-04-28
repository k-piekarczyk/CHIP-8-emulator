#include <iostream>
#include "CHIP8.hpp"
#include "Display.hpp"
#include "Input.hpp"
#include "Beeper.hpp"
#include "Timer.hpp"

int main(int argc, char **argv) {
    CHIP8 chip;

    chip.initialize();

    chip.loadRom("../roms/slipperyslope.ch8");

    Display g = Display(chip.getGFX());

    Beeper beeper = Beeper();
    Timer soundTimer = Timer(*chip.getSoundTimerPtr(), &beeper);
    Timer delayTimer = Timer(*chip.getDelayTimerPtr());

    while (g.window->isOpen()) {
        soundTimer.update();
        delayTimer.update();

        chip.next();
        g.draw();
        g.pollCloseEvent();
    }

//    Input input = Input(chip.getKeys());



//    while (!input.isFinished()) {
//
//        for(int i=0;i<30;i++) {
//            soundTimer.update();
//            delayTimer.update();
//
//            // input.update();
//            chip.next();
//            g.draw();
//        }
//    }

    return 0;
}



