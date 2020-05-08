//
// Created by Krzysiek on 31.03.2020.
//

#include "CHIP8.hpp"

#include  <iostream>
#include <fstream>
#include <random>

CHIP8::CHIP8() {
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;
}

void CHIP8::initialize() {
    clearMemory();
    clearRegisters();
    clearStack();
    clearDisplay();
    clearKeyboard();
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

void CHIP8::loadRom(std::ifstream &rom) {
    for (unsigned short i = 0x200; (i - 0x200 < Spec::MEMORY_SIZE) && rom; i++) {
        memory[i] = rom.get();
    }
    rom.close();
}

void CHIP8::loadInputHandler(Input *in) {
    this->input = in;
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

void CHIP8::clearKeyboard() {
    for (unsigned char &i : keyboard) {
        i = 0;
    }
}

void CHIP8::clearMemory() {
    for (unsigned char &i : memory) {
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
    return keyboard;
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
    printf("[%04X]: CLS\n", pc);

    clearDisplay();
    pc += 2;
}

// RET - return from a subroutine
void CHIP8::op_00EE_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: RET\n", pc);

    if (sp < 0) {
        std::cout << "The stack is empty, can't return from subroutine." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (stack[sp] < 0x200) {
        std::cout << "Attempted jump bellow instruction memory." << std::endl;
        exit(EXIT_FAILURE);
    }

    pc = stack[sp] + 2;
    sp--;
}

// SYS addr - execute a machine language subroutine at address nnn (ignored on modern interpreters)
void CHIP8::op_0nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    pc += 2;
}

// JMP addr - jump to address nnn
void CHIP8::op_1nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short addr = (b << 8) | (c << 4) | d;

    printf("[%04X]: JMP %04X\n", pc, addr);

    if (addr < 0x200) {
        std::cout << "Attempted jump bellow instruction memory." << std::endl;
        exit(EXIT_FAILURE);
    }

    pc = addr;
}

// CALL addr - execute subroutine starting at address nnn
void CHIP8::op_2nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short addr = (b << 8) | (c << 4) | d;

    printf("[%04X]: CALL %04X\n", pc, addr);

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

    printf("[%04X]: SE V%X, %02X (V%X = %02X)\n", pc, b, kk, b, V[b]);

    if (kk == V[b]) pc += 4;
    else pc += 2;
}

// SNE Vx, kk - skip the following instruction if  Vx != kk
void CHIP8::op_4xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short kk = c << 4 | d;

    printf("[%04X]: SNE V%X, %02X\n", pc, b, kk);

    if (kk != V[b]) pc += 4;
    else pc += 2;
}

// SE Vx, Vy - skip the following instruction if  Vx == Vy
void CHIP8::op_5xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: SE V%X, V%X\n", pc, b, c);

    if (V[b] == V[c]) pc += 4;
    else pc += 2;
}

// LD Vx, byte - puts value kk into register Vx
void CHIP8::op_6xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short kk = c << 4 | d;

    printf("[%04X]: LD V%X, %02X\n", pc, b, kk);

    V[b] = kk;

    pc += 2;
}

// ADD Vx, byte - adds value kk to register Vx, stores result in Vx
void CHIP8::op_7xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned char kk = c << 4 | d;

    printf("[%04X]: ADD V%X, %02X\n", pc, b, kk);

    V[b] += kk;

    pc += 2;
}

// LD Vx, Vy - stores the value of register Vy in register Vx
void CHIP8::op_8xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: LD V%X, V%X\n", pc, b, c);

    V[b] = V[c];

    pc += 2;
}

// OR Vx, Vy - performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx
void CHIP8::op_8xy1_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: OR V%X, V%X\n", pc, b, c);

    V[b] = V[b] | V[c];

    pc += 2;
}

// AND Vx, Vy - performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx
void CHIP8::op_8xy2_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: AND V%X, V%X\n", pc, b, c);

    V[b] = V[b] & V[c];

    pc += 2;
}

// XOR Vx, Vy - performs a bitwise XOR on the values of Vx and Vy, then stores the result in Vx
void CHIP8::op_8xy3_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: XOR V%X, V%X\n", pc, b, c);

    V[b] = V[b] ^ V[c];

    pc += 2;
}

// ADD Vx, Vy - adds Vx to Vy, stores the lowest 8 bits of the result in Vx, set VF = carry
void CHIP8::op_8xy4_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: ADD V%X, V%X\n", pc, b, c);

    unsigned short sum = V[b] + V[c];
    V[b] = sum & 0xFF;

    if (sum > 0xFF) V[0xF] = 1;
    else V[0xF] = 0;

    pc += 2;
}

// SUB Vx, Vy - sets VF to 1 if Vx > Vy else to 0, subtracts Vy from Vx, stores result in Vx
void CHIP8::op_8xy5_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: ADD V%X, V%X\n", pc, b, c);

    if (V[b] > V[c]) V[0xF] = 1;
    else V[0xF] = 0;

    V[b] = V[b] - V[c];

    pc += 2;
}

// SHR Vx, Vy - stores the value of register Vy shifted right one bit in register Vx, sets register VF to the least significant bit prior to the shift
void CHIP8::op_8xy6_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: SHR V%X, V%X\n", pc, b, c);

    V[0xF] = V[c] & 1;
    V[b] = V[c] >> 1;

    pc += 2;
}

// SUBN Vx, Vy - sets VF to 1 if Vy > Vx else to 0, subtracts Vx from Vy, stores result in Vx
void CHIP8::op_8xy7_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: SUBN V%X, V%X\n", pc, b, c);

    if (V[c] > V[b]) V[0xF] = 1;
    else V[0xF] = 0;

    V[b] = V[c] - V[b];

    pc += 2;
}

// SHL Vx, Vy - stores the value of register Vy shifted left one bit in register Vx, sets register VF to the least significant bit prior to the shift
void CHIP8::op_8xyE_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: SHL V%X, V%X\n", pc, b, c);

    V[0xF] = V[c] & 1;
    V[b] = V[c] << 1;

    pc += 2;
}

// SNE Vx, Vy - skips next instruction if Vx != Vy
void CHIP8::op_9xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: SNE V%X, V%X\n", pc, b, c);

    if (V[b] != V[c]) pc += 4;
    else pc += 2;
}

// LD I, addr - sets register I to nnn
void CHIP8::op_Annn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short addr = (b << 8) | (c << 4) | d;

    printf("[%04X]: LD I, %03X\n", pc, addr);

    I = addr;

    pc += 2;
}

// JMP V0, addr - jump to location nnn + V0
void CHIP8::op_Bnnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned short addr = (b << 8) | (c << 4) | d;

    printf("[%04X]: JMP V0, %03X\n", pc, addr);

    if (addr < 0x200) {
        std::cout << "Attempted jump bellow instruction memory." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (addr + V[0] > 0xFFF) {
        std::cout << "Requested jump address outside of memory." << std::endl;
        exit(EXIT_FAILURE);
    }

    pc = addr + V[0];
}

// RND Vx, byte - sets Vx to a random byte ANDed with kk
void CHIP8::op_Cxkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    unsigned char kk = c << 4 | d;

    printf("[%04X]: RND V%X, %02X\n", pc, b, kk);

    std::random_device generator;
    std::uniform_int_distribution<unsigned char> distribution(0, 0xFF);

    V[b] = distribution(generator) & kk;

    pc += 2;
}

// DRW Vx, Vy, N - draws a sprite at position Vx, Vy with N bytes of sprite data starting at address stored in I, sets VF if any pixel is unset
void CHIP8::op_Dxyn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: DRW V%X, V%X, %X\n", pc, b, c, d);

    unsigned char X = V[b] % Spec::H_SIZE;
    unsigned char Y = V[c] % Spec::V_SIZE;
    unsigned char N = d;

    bool checkForCollision, collisionDetected = false;
    unsigned int posX, posY, pos;
    for (unsigned char n = 0; n < N; n++) {
        posY = (Y + n) % Spec::V_SIZE;
        for (unsigned char x = 0; x < 8; x++) {
            checkForCollision = false;
            posX = (X + x) % Spec::H_SIZE;
            pos = (posY * 64) + posX;

            if (!collisionDetected && gfx[pos]) checkForCollision = true;

            gfx[pos] = gfx[pos] ^ ((memory[I + n] >> (7 - x)) & 1);

            if (checkForCollision)
                if (!gfx[pos]) collisionDetected = true;
        }
    }

    if (collisionDetected) V[0xF] = 1;

    pc += 2;
}

// SKP Vx - skips next instruction if key with the value of Vx is pressed
void CHIP8::op_Ex9E_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: SKP V%X\n", pc, b);

    if (keyboard[V[b]]) pc += 4;
    else pc += 2;
}

// SKNP Vx - skips next instruction if key with the value of Vx is not pressed
void CHIP8::op_ExA1_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: SKNP V%X\n", pc, b);

    if (!keyboard[V[b]]) pc += 4;
    else pc += 2;
}

// LD Vx, DT - stores the current delay timer value in Vx
void CHIP8::op_Fx07_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: LD V%X, DT\n", pc, b);

    V[b] = delayTimer;
    pc += 2;
}

// LD Vx, K - waits for a key press, stores the value of key press in Vx
void CHIP8::op_Fx0A_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: LD V%X, K\n", pc, b);

    input->await();
    for (int i = 0; i < Spec::NUMBER_OF_KEYS; i++)
        if (V[i]) {
            V[b] = i;
            break;
        }
    pc += 2;
}

// LD DT, Vx - sets a delay timer to value from Vx
void CHIP8::op_Fx15_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: LD DT, V%X\n", pc, b);

    delayTimer = V[b];
    pc += 2;
}

// LD ST, Vx - sets a delay timer to value from Vx
void CHIP8::op_Fx18_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: LD ST, V%X\n", pc, b);
    soundTimer = V[b];
    pc += 2;
}

// ADD I, Vx - adds Vx to I, stores result in I
void CHIP8::op_Fx1E_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: ADD I, V%X\n", pc, b);

    unsigned short newI = I + V[b];

    if (newI > 0xFFF) {
        std::cout << "Attempted addressing outside of memory." << std::endl;
        exit(EXIT_FAILURE);
    }

    I = newI;
    pc += 2;
}

// LD F, Vx - sets I to font with the hexadecimal value of Vx
void CHIP8::op_Fx29_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: LD F, V%X\n", pc, b);

    if (V[b] > 0xF) {
        std::cout << "Attempted setting fonts outside of range: <0, 0xF>" << std::endl;
        exit(EXIT_FAILURE);
    }

    I = 0x50 + (V[b] * 5);
    pc += 2;
}

// LD B, Vx - sets I, I+1, I+2 to BCD coded hundreds, tenths and ones based on value in Vx
void CHIP8::op_Fx33_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: LD B, V%X\n", pc, b);

    memory[I] = V[b] / 100;
    unsigned char rem = V[b] % 100;

    memory[I + 1] = rem / 10;
    memory[I + 2] = rem % 10;

    pc += 2;
}

// LD [I], Vx - stores values from registers V0 through Vx in memory starting at I, then increments I by x+1
void CHIP8::op_Fx55_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: LD [I], V%X\n", pc, b);

    for (int i = 0; i <= b; i++) {
        memory[I + i] = V[i];
    }

    I += b + 1;

    pc += 2;
}

// LD Vx, [I] - loads values into registers V0 through Vx from memory starting at I, then increments I by x+1
void CHIP8::op_Fx65_(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    printf("[%04X]: V%X, LD [I]\n", pc, b);

    for (int i = 0; i <= b; i++) {
        V[i] = memory[I + i];
    }

    I += b + 1;
    pc += 2;
}


