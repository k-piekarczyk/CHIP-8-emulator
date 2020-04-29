#include "CHIP8.hpp"
#include "Display.hpp"
#include "Beeper.hpp"
#include "Timer.hpp"

int main(int argc, char **argv) {
    CHIP8 chip;

    chip.initialize();

    chip.loadRom("../roms/pong.ch8");

    Display g = Display(chip.getGFX());
    Input input = Input(chip.getKeys(), g.window);
    chip.loadInputHandler(&input);


    Timer soundTimer = Timer(*chip.getSoundTimerPtr(), true);
    Timer delayTimer = Timer(*chip.getDelayTimerPtr());

    while (g.window->isOpen()) {
        input.update();
        soundTimer.update();
        delayTimer.update();

        chip.next();
        g.draw();

//        sf::sleep(sf::microseconds(1000));
    }

    return 0;
}

