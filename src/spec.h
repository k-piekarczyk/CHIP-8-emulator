//
// Created by Krzysiek on 31.03.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_SPEC_H
#define PROJEKT_INDYWIDUALNY_SPEC_H

class Spec {
public:
    static const int SCALE = 10;

    static const int H_SIZE = 64;
    static const int V_SIZE = 32;
    static const int DISPLAY_SIZE = V_SIZE * H_SIZE;

    static const int MEMORY_SIZE = 4096;
    static const int STACK_SIZE = 16;
    static const int NUMBER_OF_REGISTERS = 16;

    static const int CHIP_FREQUENCY = 500;
    static const int TIMER_FREQUENCY = 60;

private:
    Spec() = default;
};


#endif //PROJEKT_INDYWIDUALNY_SPEC_H
