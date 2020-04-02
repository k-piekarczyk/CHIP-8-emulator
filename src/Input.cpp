//
// Created by Krzysiek on 02.04.2020.
//

#include <SDL.h>

#include "Input.h"

Input::Input(unsigned char *keys) : keys(keys) {}

void Input::update() {
    SDL_Event e;
    clearKeys();

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_1:
                        keys[0x0] = 0xFF;
                        break;
                    case SDLK_2:
                        keys[0x1] = 0xFF;
                        break;
                    case SDLK_3:
                        keys[0x2] = 0xFF;
                        break;
                    case SDLK_4:
                        keys[0x3] = 0xFF;
                        break;
                    case SDLK_q:
                        keys[0x4] = 0xFF;
                        break;
                    case SDLK_w:
                        keys[0x5] = 0xFF;
                        break;
                    case SDLK_e:
                        keys[0x6] = 0xFF;
                        break;
                    case SDLK_r:
                        keys[0x7] = 0xFF;
                        break;
                    case SDLK_a:
                        keys[0x8] = 0xFF;
                        break;
                    case SDLK_s:
                        keys[0x9] = 0xFF;
                        break;
                    case SDLK_d:
                        keys[0xA] = 0xFF;
                        break;
                    case SDLK_f:
                        keys[0xB] = 0xFF;
                        break;
                    case SDLK_z:
                        keys[0xC] = 0xFF;
                        break;
                    case SDLK_x:
                        keys[0xD] = 0xFF;
                        break;
                    case SDLK_c:
                        keys[0xE] = 0xFF;
                        break;
                    case SDLK_v:
                        keys[0xF] = 0xFF;
                        break;
                }
        }
    }
}

bool Input::isFinished() {
    return quit;
}

void Input::clearKeys() {
    for (char i = 0x0; i < 0x10; i++) {
        keys[i] = 0x0;
    }
}