//
// Created by Krzysiek on 01.04.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_GRAPHICS_H
#define PROJEKT_INDYWIDUALNY_GRAPHICS_H

#include <SDL.h>

#include "spec.h"

class Graphics {
    unsigned char * frame;
    SDL_Window * window;
    SDL_Renderer * renderer;

public:
    explicit Graphics(unsigned char * gfx);
    ~Graphics();

    void draw();
};


#endif //PROJEKT_INDYWIDUALNY_GRAPHICS_H
