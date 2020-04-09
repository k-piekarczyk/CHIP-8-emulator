//
// Created by Krzysiek on 02.04.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_INPUT_H
#define PROJEKT_INDYWIDUALNY_INPUT_H

#include <SDL.h>

class Input {
    unsigned char * keys;
    bool quit = false;

public:
    explicit Input(unsigned char * keys);

    void update();
    void await();
    bool isFinished();

private:
    void clearKeys();

    bool handleKeyPress(SDL_Event *e);


};


#endif //PROJEKT_INDYWIDUALNY_INPUT_H
