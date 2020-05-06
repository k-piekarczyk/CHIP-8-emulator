//
// Created by Krzysiek on 06.05.2020.
//


#include "Runner.hpp"

#include <fstream>

Runner::Runner(std::ifstream &rom) : g(chip.getGFX()), input(chip.getKeys(), g.window),
                                       soundTimer(*chip.getSoundTimerPtr(), true),
                                       delayTimer(*chip.getDelayTimerPtr()) {
    chip.initialize();
    chip.loadRom(rom);
    chip.loadInputHandler(&input);
}

void Runner::start() {
    while (g.window->isOpen() && !stopSig) {
        input.update();
        soundTimer.update();
        delayTimer.update();

        chip.next();
        g.draw();

        // sf::sleep(sf::microseconds(1000));
    }
}

void Runner::stop() {
    stopSig = true;
}
