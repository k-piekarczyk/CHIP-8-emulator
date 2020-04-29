//
// Created by Krzysiek on 02.04.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_TIMER_HPP
#define PROJEKT_INDYWIDUALNY_TIMER_HPP

#include <chrono>

#include "Beeper.hpp"

class Timer {
    unsigned char &value;
    Beeper * beeper = nullptr;
    std::chrono::steady_clock::time_point timer;

public:
    explicit Timer(unsigned char &v);

    Timer(unsigned char &v, bool beeperCheck);

    void update();
};


#endif //PROJEKT_INDYWIDUALNY_TIMER_HPP
