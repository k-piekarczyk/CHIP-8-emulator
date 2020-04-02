//
// Created by Krzysiek on 02.04.2020.
//

#include "Timer.h"
#include "spec.h"

Timer::Timer(unsigned char &v) : value(v) {
    timer = std::chrono::steady_clock::now();
}

Timer::Timer(unsigned char &v, Beeper *beeper) : value(v), beeper(beeper) {}

void Timer::update() {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timer).count() <
        1000 / Spec::TIMER_FREQUENCY)
        return;

    if (value > 0) {
        if (beeper != nullptr) beeper->beep();
        value--;
    }

    timer = std::chrono::steady_clock::now();
}