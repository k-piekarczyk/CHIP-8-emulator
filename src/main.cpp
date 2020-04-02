#include <iostream>
#include <chrono>

#include "CHIP8.h"
#include "Graphics.h"
#include "Input.h"
#include "Beeper.h"
#include "Timer.h"

#include <windows.h>

int main(int argc, char** argv) {

    CHIP8 chip;

    chip.initialize();

    Graphics g = Graphics(chip.getGFX());
    Input input = Input(chip.getKeys());

    Beeper beeper = Beeper();

    Timer soundTimer = Timer(*chip.getSoundTimerPtr(), &beeper);
    Timer delayTimer = Timer(*chip.getDelayTimerPtr());

    chip.loadRom("../roms/heart_monitor.ch8");

    while (!input.isFinished()) {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        bool cycleCompleted = true;

        int opInCycle = 0;

        for (int i = 0; i < Spec::CHIP_FREQUENCY; i++) {
            opInCycle++;
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 1000) {
                cycleCompleted = false;
                break;
            }

            soundTimer.update();
            delayTimer.update();

            input.update();
            chip.next();
            g.draw();
        }

        std::cout << opInCycle << std::endl;

        if(!cycleCompleted) SDL_Delay(1000 - (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()));
    }

    return 0;
}
