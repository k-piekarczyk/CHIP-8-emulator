//
// Created by Krzysiek on 02.04.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_TIMER_H
#define PROJEKT_INDYWIDUALNY_TIMER_H

#include <chrono>

#include "Beeper.h"

class Timer {
    unsigned char &value;
    Beeper *beeper = nullptr;
    std::chrono::steady_clock::time_point timer;

public:
    explicit Timer(unsigned char &v);

    Timer(unsigned char &v, Beeper *beeper);

    void update();
};


#endif //PROJEKT_INDYWIDUALNY_TIMER_H
