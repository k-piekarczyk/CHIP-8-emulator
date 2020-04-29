//
// Created by Krzysiek on 02.04.2020.
//

#include "Timer.hpp"
#include "spec.hpp"

Timer::Timer(unsigned char &v) : value(v) {
    timer = std::chrono::steady_clock::now();
}

Timer::Timer(unsigned char &v, bool beeperCheck) : Timer(v) {
    if(beeperCheck) beeper = new Beeper();
}

void Timer::update() {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timer).count() <
        1000 / Spec::TIMER_FREQUENCY)
        return;

    if (value > 0) {
        if (beeper != nullptr) beeper->start();
        value--;
    } else if (beeper != nullptr) beeper->stop();

    timer = std::chrono::steady_clock::now();
}