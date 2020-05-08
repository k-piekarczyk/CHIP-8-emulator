//
// Created by Krzysiek on 06.05.2020.
//


#include "Runner.hpp"

#include <fstream>

Runner::Runner(std::ifstream &rom, bool delay) : g(chip.getGFX()), input(chip.getKeys(), g.window),
                                       soundTimer(*chip.getSoundTimerPtr(), true),
                                       delayTimer(*chip.getDelayTimerPtr()), delay(delay) {
    chip.initialize();
    chip.loadRom(rom);
    chip.loadInputHandler(&input);
}


void Runner::start() {
    std::chrono::steady_clock::time_point lastDraw = std::chrono::steady_clock::now();
    while (g.window->isOpen()) {
        input.update();
        soundTimer.update();
        delayTimer.update();
        chip.next();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastDraw).count() < 16){
            g.draw();
            lastDraw = std::chrono::steady_clock::now();
        }
        if(delay) sf::sleep(sf::milliseconds(1));
    }
}
