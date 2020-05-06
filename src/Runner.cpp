//
// Created by Krzysiek on 06.05.2020.
//

#include "Runner.hpp"

Runner::Runner(const char *fileName) : g(chip.getGFX()), input(chip.getKeys(), g.window),
                                       soundTimer(*chip.getSoundTimerPtr(), true),
                                       delayTimer(*chip.getDelayTimerPtr()) {
    chip.initialize();
    chip.loadRom(fileName);
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
