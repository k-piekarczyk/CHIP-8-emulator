//
// Created by Krzysiek on 31.03.2020.
//

#include "CHIP8.h"

#include <iostream>
#include <fstream>

CHIP8::CHIP8() {
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;
}

void CHIP8::initialize() {
    clearRegisters();
    clearStack();
    clearDisplay();
    clearKeys();
    loadFontset();
    initializeOpcodeArray();
}

void CHIP8::step() {
    if (pc > 0xFFF) {
        std::cout << "Program counter larger than 0xFFF (outside memory bounds)." << std::endl;
        exit(EXIT_FAILURE);
    }

    fetch();
    decode();
    execute();
}

void CHIP8::loadRom(const char *fileName) {
    std::ifstream source = std::ifstream(fileName, std::ios_base::binary);

    for (unsigned short i = 0x200; (i - 0x200 < Spec::MEMORY_SIZE) && source; i++) {
        memory[i] = source.get();
    }
    source.close();
}

void CHIP8::fetch() {
    opcode = memory[pc] << 8 | memory[pc + 1];
}

void CHIP8::decode() {
    char a = (opcode & 0xF000) >> 12;
    char b = (opcode & 0x0F00) >> 8;
    char c = (opcode & 0x00F0) >> 4;
    char d = opcode & 0x000F;

    opcode_func = opcode_arr[a][b][c][d];

    if (opcode_func == nullptr) {
        std::cout << "Unknown opcode encountered." << std::endl;
        exit(EXIT_SUCCESS);
    }
}

void CHIP8::execute() {
    char a = (opcode & 0xF000) >> 12;
    char b = (opcode & 0x0F00) >> 8;
    char c = (opcode & 0x00F0) >> 4;
    char d = opcode & 0x000F;

    (this->*opcode_func)(a, b, c, d);
}

void CHIP8::clearDisplay() {
    for (unsigned char &i : gfx) {
        i = 0;
    }
}

void CHIP8::clearStack() {
    for (unsigned short &i : stack) {
        i = 0;
    }
}

void CHIP8::clearRegisters() {
    for (unsigned char &i : V) {
        i = 0;
    }
}

void CHIP8::clearKeys() {
    for (unsigned char &i : key) {
        i = 0;
    }
}

unsigned char *CHIP8::getGFX() {
    return gfx;
}

unsigned char *CHIP8::getKeys() {
    return key;
}


void CHIP8::loadFontset() {
    for (int i = 0; i < 0x50; i++) {
        memory[i + 0x50] = Spec::FONTSET[i];
    }
}


void CHIP8::op_00E0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 00E0 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_00EE_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 00EE ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_0nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 0nnn ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_1nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 1nnn ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_2nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 2nnn ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_3xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 3xkk ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_4xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 4xkk ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_5xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 5xy0 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_6xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 6xkk ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_7xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 7xkk ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_8xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 8xy0 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_8xy1_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 8xy1 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_8xy2_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 8xy2 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_8xy3_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 8xy3 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_8xy4_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 8xy4 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_8xy5_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 8xy5 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_8xy6_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 8xy6 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_8xy7_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 8xy7 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_8xyE_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 8xyE ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_9xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ 9xy0 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Annn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Annn ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Bnnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Bnnn ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Cxkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Cxkk ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Dxyn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Dxyn ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Ex9E_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Ex9E ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_ExA1_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ ExA1 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Fx07_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Fx07 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Fx0A_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Fx0A ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Fx15_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Fx15 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Fx18_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Fx18 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Fx1E_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Fx1E ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Fx29_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Fx29 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Fx33_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Fx33 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Fx55_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Fx55 ] opcode not implemented" << std::endl;
    pc += 2;
}

void CHIP8::op_Fx65_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    std::cout << "[ Fx65 ] opcode not implemented" << std::endl;
    pc += 2;
}
