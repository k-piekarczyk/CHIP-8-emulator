//
// Created by Krzysiek on 01.04.2020.
//

#include <iostream>
#include "Display.hpp"

Display::Display(unsigned char * gfx) : frame(gfx) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
            "CHIP-8 Emulator",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            Spec::H_SIZE * Spec::SCALE,
            Spec::V_SIZE * Spec::SCALE,
            SDL_WINDOW_SHOWN
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

Display::~Display() {
    frame = nullptr;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::draw() {
    SDL_RenderClear(renderer);

    SDL_Rect currentPixel;
    currentPixel.h = Spec::SCALE;
    currentPixel.w = Spec::SCALE;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int y = 0; y < Spec::V_SIZE; y++) {
        for (int x = 0; x < Spec::H_SIZE; x++) {

            if (frame[(y * Spec::H_SIZE) + x]) {
                currentPixel.x = x * Spec::SCALE;
                currentPixel.y = y * Spec::SCALE;

                SDL_RenderFillRect(renderer, &currentPixel);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}