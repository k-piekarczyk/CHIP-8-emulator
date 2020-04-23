//
// Created by Krzysiek on 02.04.2020.
//



#include <iostream>
#include "Input.h"

Input::Input(unsigned char *keys) : keys(keys) {}

void Input::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        handleKeyPress(&e);
    }
}

void Input::await() {
    SDL_Event e;
    do SDL_WaitEvent(&e);
    while(!handleKeyPress(&e));
}

bool Input::handleKeyPress(SDL_Event * e) {
    bool allowedEvent = true;
    switch (e->type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (e->key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_1:
                    keys[0x1] = 0xFF;
                    break;
                case SDLK_2:
                    keys[0x2] = 0xFF;
                    break;
                case SDLK_3:
                    keys[0x3] = 0xFF;
                    break;
                case SDLK_4:
                    keys[0xC] = 0xFF;
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
                    keys[0xD] = 0xFF;
                    break;
                case SDLK_a:
                    keys[0x7] = 0xFF;
                    break;
                case SDLK_s:
                    keys[0x8] = 0xFF;
                    break;
                case SDLK_d:
                    keys[0x9] = 0xFF;
                    break;
                case SDLK_f:
                    keys[0xE] = 0xFF;
                    break;
                case SDLK_z:
                    keys[0xA] = 0xFF;
                    break;
                case SDLK_x:
                    keys[0x0] = 0xFF;
                    break;
                case SDLK_c:
                    keys[0xB] = 0xFF;
                    break;
                case SDLK_v:
                    keys[0xF] = 0xFF;
                    break;
                default:
                    allowedEvent = false;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (e->key.keysym.sym) {
                case SDLK_1:
                    keys[0x1] = 0;
                    break;
                case SDLK_2:
                    keys[0x2] = 0;
                    break;
                case SDLK_3:
                    keys[0x3] = 0;
                    break;
                case SDLK_4:
                    keys[0xC] = 0;
                    break;
                case SDLK_q:
                    keys[0x4] = 0;
                    break;
                case SDLK_w:
                    keys[0x5] = 0;
                    break;
                case SDLK_e:
                    keys[0x6] = 0;
                    break;
                case SDLK_r:
                    keys[0xD] = 0;
                    break;
                case SDLK_a:
                    keys[0x7] = 0;
                    break;
                case SDLK_s:
                    keys[0x8] = 0;
                    break;
                case SDLK_d:
                    keys[0x9] = 0;
                    break;
                case SDLK_f:
                    keys[0xE] = 0;
                    break;
                case SDLK_z:
                    keys[0xA] = 0;
                    break;
                case SDLK_x:
                    keys[0x0] = 0;
                    break;
                case SDLK_c:
                    keys[0xB] = 0;
                    break;
                case SDLK_v:
                    keys[0xF] = 0;
                    break;
                default:
                    allowedEvent = false;
                    break;
            }
        default:
            allowedEvent = false;
            break;
    }

    return allowedEvent;
}

bool Input::isFinished() {
    return quit;
}

void Input::clearKeys() {
    for (char i = 0x0; i < 0x10; i++) {
        keys[i] = 0x0;
    }
}