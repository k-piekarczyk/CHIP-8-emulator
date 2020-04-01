//
// Created by Krzysiek on 31.03.2020.
//

#include "CHIP8.h"

CHIP8::CHIP8() {
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;
}