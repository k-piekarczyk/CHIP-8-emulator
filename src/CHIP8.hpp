//
// Created by Krzysiek on 31.03.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_CHIP8_H
#define PROJEKT_INDYWIDUALNY_CHIP8_H

#include "spec.hpp"
#include "Input.hpp"


class CHIP8 {
protected:
    unsigned short opcode;
    unsigned char memory[Spec::MEMORY_SIZE]{};
    unsigned char V[Spec::NUMBER_OF_REGISTERS]{};
    unsigned short I;
    unsigned short pc;

    unsigned char gfx[Spec::DISPLAY_SIZE]{};

    unsigned char delayTimer{};
    unsigned char soundTimer{};

    unsigned short stack[Spec::STACK_SIZE]{};
    unsigned char sp;

    unsigned char keyboard[Spec::NUMBER_OF_KEYS]{};

    Input *input;

    void (CHIP8::*opcode_arr[0x10][0x10][0x10][0x10])(unsigned char, unsigned char, unsigned char, unsigned char);

    void (CHIP8::*opcode_func)(unsigned char, unsigned char, unsigned char, unsigned char);

    bool verbose = true;

public:
    void initialize();

    void next();

    void loadRom(std::ifstream &rom);

    void loadInputHandler(Input *in);

    unsigned char *getGFX();

    unsigned char *getKeys();

    unsigned char *getDelayTimerPtr();

    unsigned char *getSoundTimerPtr();

protected:
    void clearDisplay();

    void clearStack();

    void clearRegisters();

    void clearKeyboard();

    void clearMemory();

    void resetTimers();

    void loadFontset();

    void initializeOpcodeArray();

    void fetch();

    void decode();

    void execute();

    void op_00E0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_00EE_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_0nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_1nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_2nnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_3xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_4xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_5xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_6xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_7xkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_8xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_8xy1_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_8xy2_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_8xy3_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_8xy4_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_8xy5_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_8xy6_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_8xy7_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_8xyE_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_9xy0_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Annn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Bnnn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Cxkk_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Dxyn_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Ex9E_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_ExA1_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Fx07_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Fx0A_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Fx15_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Fx18_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Fx1E_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Fx29_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Fx33_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Fx55_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

    void op_Fx65_(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
};

#endif //PROJEKT_INDYWIDUALNY_CHIP8_H