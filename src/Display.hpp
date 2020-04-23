//
// Created by Krzysiek on 01.04.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_GRAPHICS_H
#define PROJEKT_INDYWIDUALNY_GRAPHICS_H

#include <SDL.h>

#include "spec.hpp"

class Display {
    unsigned char * frame;
    SDL_Window * window;
    SDL_Renderer * renderer;

public:
    explicit Display(unsigned char * gfx);
    ~Display();

    void draw();
};


#endif //PROJEKT_INDYWIDUALNY_GRAPHICS_H
