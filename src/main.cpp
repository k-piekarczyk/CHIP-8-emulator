#include <iostream>

#include "CHIP8.h"
#include "Graphics.h"

int main() {
    CHIP8 chip;

    chip.initialize();

    Graphics g = Graphics(chip.getGFX());
}
