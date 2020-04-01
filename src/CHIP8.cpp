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
