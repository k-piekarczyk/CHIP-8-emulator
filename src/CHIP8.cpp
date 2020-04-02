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
    resetTimers();
    loadFontset();
    initializeOpcodeArray();
}

void CHIP8::next() {
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

void CHIP8::resetTimers() {
    delayTimer = 0;
    soundTimer = 0;
}

unsigned char *CHIP8::getGFX() {
    return gfx;
}

unsigned char *CHIP8::getKeys() {
    return key;
}

unsigned char *CHIP8::getDelayTimerPtr() {
    return &delayTimer;
}

unsigned char *CHIP8::getSoundTimerPtr() {
    return &soundTimer;
}

void CHIP8::loadFontset() {
    unsigned char fontset[80] =
            {
                    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                    0x20, 0x60, 0x20, 0x20, 0x70, // 1
                    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
            };

    for (int i = 0; i < 0x50; i++) {
        memory[i + 0x50] = fontset[i];
    }
}

void CHIP8::initializeOpcodeArray() {
    for (int i = 0; i < 0x10; i++) {
        for (int j = 0; j < 0x10; j++) {
            for (int k = 0; k < 0x10; k++) {
                for (int l = 0; l < 0x10; l++) {

                    switch (i) {
                        case 0x0:
                            if (j == 0x0 && k == 0xE) {
                                if (l == 0x0) opcode_arr[i][j][k][l] = &CHIP8::op_00E0_;
                                else if (l == 0xE) opcode_arr[i][j][k][l] = &CHIP8::op_00EE_;
                            } else opcode_arr[i][j][k][l] = &CHIP8::op_0nnn_;
                            break;

                        case 0x1:
                            opcode_arr[i][j][k][l] = &CHIP8::op_1nnn_;
                            break;

                        case 0x2:
                            opcode_arr[i][j][k][l] = &CHIP8::op_2nnn_;
                            break;

                        case 0x3:
                            opcode_arr[i][j][k][l] = &CHIP8::op_3xkk_;
                            break;

                        case 0x4:
                            opcode_arr[i][j][k][l] = &CHIP8::op_4xkk_;
                            break;

                        case 0x5:
                            opcode_arr[i][j][k][l] = &CHIP8::op_5xy0_;
                            break;

                        case 0x6:
                            opcode_arr[i][j][k][l] = &CHIP8::op_6xkk_;
                            break;

                        case 0x7:
                            opcode_arr[i][j][k][l] = &CHIP8::op_7xkk_;
                            break;

                        case 0x8:
                            switch (l) {
                                case 0x0:
                                    opcode_arr[i][j][k][l] = &CHIP8::op_8xy0_;
                                    break;

                                case 0x1:
                                    opcode_arr[i][j][k][l] = &CHIP8::op_8xy1_;
                                    break;

                                case 0x2:
                                    opcode_arr[i][j][k][l] = &CHIP8::op_8xy2_;
                                    break;

                                case 0x3:
                                    opcode_arr[i][j][k][l] = &CHIP8::op_8xy3_;
                                    break;

                                case 0x4:
                                    opcode_arr[i][j][k][l] = &CHIP8::op_8xy4_;
                                    break;

                                case 0x5:
                                    opcode_arr[i][j][k][l] = &CHIP8::op_8xy5_;
                                    break;

                                case 0x6:
                                    opcode_arr[i][j][k][l] = &CHIP8::op_8xy6_;
                                    break;

                                case 0x7:
                                    opcode_arr[i][j][k][l] = &CHIP8::op_8xy7_;
                                    break;

                                case 0xE:
                                    opcode_arr[i][j][k][l] = &CHIP8::op_8xyE_;
                                    break;
                            }
                            break;

                        case 0x9:
                            opcode_arr[i][j][k][l] = &CHIP8::op_9xy0_;
                            break;

                        case 0xA:
                            opcode_arr[i][j][k][l] = &CHIP8::op_Annn_;
                            break;

                        case 0xB:
                            opcode_arr[i][j][k][l] = &CHIP8::op_Bnnn_;
                            break;

                        case 0xC:
                            opcode_arr[i][j][k][l] = &CHIP8::op_Cxkk_;
                            break;

                        case 0xD:
                            opcode_arr[i][j][k][l] = &CHIP8::op_Dxyn_;
                            break;

                        case 0xE:
                            if (k == 0x9 && l == 0xE) opcode_arr[i][j][k][l] = &CHIP8::op_Ex9E_;
                            else if (k == 0xA && l == 0x1) opcode_arr[i][j][k][l] = &CHIP8::op_ExA1_;
                            break;

                        case 0xF:
                            if (k == 0x0 && l == 0x7) opcode_arr[i][j][k][l] = &CHIP8::op_Fx07_;
                            else if (k == 0x0 && l == 0xA) opcode_arr[i][j][k][l] = &CHIP8::op_Fx0A_;
                            else if (k == 0x1 && l == 0x5) opcode_arr[i][j][k][l] = &CHIP8::op_Fx15_;
                            else if (k == 0x1 && l == 0x8) opcode_arr[i][j][k][l] = &CHIP8::op_Fx18_;
                            else if (k == 0x1 && l == 0xE) opcode_arr[i][j][k][l] = &CHIP8::op_Fx1E_;
                            else if (k == 0x2 && l == 0x9) opcode_arr[i][j][k][l] = &CHIP8::op_Fx29_;
                            else if (k == 0x3 && l == 0x3) opcode_arr[i][j][k][l] = &CHIP8::op_Fx33_;
                            else if (k == 0x5 && l == 0x5) opcode_arr[i][j][k][l] = &CHIP8::op_Fx55_;
                            else if (k == 0x6 && l == 0x5) opcode_arr[i][j][k][l] = &CHIP8::op_Fx65_;
                            break;
                    }
                }
            }
        }
    }
}

// CLS - clear screen
void CHIP8::op_00E0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    clearDisplay();
    pc += 2;
}

// RET - return from a subroutine
void CHIP8::op_00EE_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    if (sp < 0) {
        std::cout << "The stack is empty, can't return from subroutine." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (stack[sp] < 0x200) {
        std::cout << "Attempted jump bellow instruction memory." << std::endl;
        exit(EXIT_FAILURE);
    }

    pc = stack[sp];
    sp--;
}

// SYS addr - execute a machine language subroutine at address nnn (ignored on modern interpreters)
void CHIP8::op_0nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    pc += 2;
}

// JMP addr - jump to address nnn
void CHIP8::op_1nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short addr = (b << 8) | (c << 4) | d;

    if (addr < 0x200) {
        std::cout << "Attempted jump bellow instruction memory." << std::endl;
        exit(EXIT_FAILURE);
    }

    pc = addr;
}

// CALL addr - execute subroutine starting at address nnn
void CHIP8::op_2nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short addr = (b << 8) | (c << 4) | d;

    if (addr < 0x200) {
        std::cout << "Attempted jump bellow instruction memory." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (sp >= Spec::STACK_SIZE) {
        std::cout << "Stack size exceeded." << std::endl;
        exit(EXIT_FAILURE);
    }

    sp++;
    stack[sp] = pc;
    pc = addr;
}

// SE Vx, kk - skip the following instruction if  Vx == kk
void CHIP8::op_3xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short kk = c << 4 | d;
    if (kk == V[b]) pc += 4;
    else pc += 2;
}

// SNE Vx, kk - skip the following instruction if  Vx != kk
void CHIP8::op_4xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short kk = c << 4 | d;
    if (kk != V[b]) pc += 4;
    else pc += 2;
}

// SNE Vx, Vy - skip the following instruction if  Vx == Vy
void CHIP8::op_5xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    if (V[b] == V[c]) pc += 4;
    else pc += 2;
}

// LD Vx, byte - puts value kk into register Vx
void CHIP8::op_6xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short kk = c << 4 | d;
    V[b] = kk;

    pc += 2;
}

// ADD Vx, byte - adds value kk to register Vx, stores result in Vx
void CHIP8::op_7xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned char kk = c << 4 | d;
    V[b] += kk;

    pc += 2;
}

// LD Vx, Vy - stores the value of register Vy in register Vx
void CHIP8::op_8xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    V[b] = V[c];

    pc += 2;
}

// OR Vx, Vy - performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx
void CHIP8::op_8xy1_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    V[b] = V[b] | V[c];

    pc += 2;
}

// AND Vx, Vy - performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx
void CHIP8::op_8xy2_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    V[b] = V[b] & V[c];

    pc += 2;
}

// XOR Vx, Vy - performs a bitwise XOR on the values of Vx and Vy, then stores the result in Vx
void CHIP8::op_8xy3_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    V[b] = V[b] ^ V[c];

    pc += 2;
}

// ADD Vx, Vy - adds Vx to Vy, stores the lowest 8 bits of the result in Vx, set VF = carry
void CHIP8::op_8xy4_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short sum = V[b] + V[c];
    V[b] = sum & 0xFF;

    if (sum > 0xFF) V[0xF] = 1;
    else V[0xF] = 0;

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
