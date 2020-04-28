#include "CHIP8.hpp"
#include "Display.hpp"
#include "Beeper.hpp"
#include "Timer.hpp"

int main(int argc, char **argv) {
    CHIP8 chip;

    chip.initialize();

    chip.loadRom("../roms/slipperyslope.ch8");

    Display g = Display(chip.getGFX());
    Input input = Input(chip.getKeys(), g.window);
    chip.loadInputHandler(&input);

    Beeper beeper = Beeper();
    Timer soundTimer = Timer(*chip.getSoundTimerPtr(), &beeper);
    Timer delayTimer = Timer(*chip.getDelayTimerPtr());

    while (g.window->isOpen()) {
        input.update();
        soundTimer.update();
        delayTimer.update();

        chip.next();
        g.draw();
    }

    return 0;
}



