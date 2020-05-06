//
// Created by Krzysiek on 06.05.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_RUNNER_HPP
#define PROJEKT_INDYWIDUALNY_RUNNER_HPP

#include "CHIP8.hpp"
#include "Display.hpp"
#include "Beeper.hpp"
#include "Timer.hpp"

class Runner {
    bool stopSig = false;
    CHIP8 chip;

    Display g;
    Input input;
    Timer soundTimer;
    Timer delayTimer;

public:
    explicit Runner(const char *fileName);

    void start();
    void stop();

private:
    void chipLoop();
};


#endif //PROJEKT_INDYWIDUALNY_RUNNER_HPP
