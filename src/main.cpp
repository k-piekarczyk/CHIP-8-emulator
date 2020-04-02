#include <iostream>
#include <chrono>

#include "CHIP8.h"
#include "Graphics.h"
#include "Input.h"

int main(int argc, char** argv) {
    CHIP8 chip;

    chip.initialize();

    Graphics g = Graphics(chip.getGFX());
    Input input = Input(chip.getKeys());

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

            input.update();
            chip.step();
            g.draw();
        }

        std::cout << opInCycle << std::endl;

        if(!cycleCompleted) SDL_Delay(1000 - (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count()));
    }

    return 0;
}
