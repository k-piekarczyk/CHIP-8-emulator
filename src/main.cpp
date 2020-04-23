#include <iostream>
#include <chrono>

#include "CHIP8.h"
#include "Graphics.h"
#include "Input.h"
#include "Beeper.h"
#include "Timer.h"


int main(int argc, char **argv) {
    CHIP8 chip;

    chip.initialize();

    Graphics g = Graphics(chip.getGFX());
    Input input = Input(chip.getKeys());

    Beeper beeper = Beeper();
    Timer soundTimer = Timer(*chip.getSoundTimerPtr(), &beeper);
    Timer delayTimer = Timer(*chip.getDelayTimerPtr());

    chip.loadRom("../roms/PONG");

    chip.loadInputHandler(&input);

    while (!input.isFinished()) {

        auto start = std::chrono::steady_clock::now();
        auto cycleCounter = 0;
        while (!input.isFinished() &&
               std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() < 10) {
            soundTimer.update();
            delayTimer.update();

            input.update();
            chip.next();
            g.draw();

            cycleCounter++;
            SDL_Delay(1);
        }
        std::cout << "Number of cycles: " << cycleCounter << ", avg freq [10s]: " << cycleCounter / 10.0 << std::endl;
    }

    return 0;
}
