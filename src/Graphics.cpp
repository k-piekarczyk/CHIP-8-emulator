//
// Created by Krzysiek on 01.04.2020.
//

#include <iostream>
#include "Graphics.h"

Graphics::Graphics(unsigned char * gfx) : frame(gfx) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
            "CHIP-8 Emulator",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            Spec::H_SIZE * Spec::SCALE,
            Spec::V_SIZE * Spec::SCALE,
            SDL_WINDOW_MAXIMIZED
    );

    if (window == nullptr) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "Could not create a renderer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

Graphics::~Graphics() {
    frame = nullptr;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}