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
    CHIP8 chip;

    Display g;
    Input input;
    Timer soundTimer;
    Timer delayTimer;

    bool delay;

public:
    explicit Runner(std::ifstream &rom, bool delay);

    void start();
};


#endif //PROJEKT_INDYWIDUALNY_RUNNER_HPP
