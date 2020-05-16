//
// Created by Krzysiek on 08.05.2020.
//

#include "Tester.hpp"

void Tester::runTests() {

    TestOutcome testOutcomes[35];
    int succeded = 0;
    int skipped = 0;
    int failed = 0;

    for (int i = 0; i < 35; i++) {
        beforeEach();
        testOutcomes[i] = (this->*opcode_test_arr[i])();
    }

    std::cout << "Successful tests:" << std::endl;
    for (const TestOutcome &outcome : testOutcomes)
        if (outcome.success) {
            std::cout << "\t- " << outcome.name << std::endl;
            succeded++;
        }
    std::cout << std::endl;

    std::cout << "Skipped tests:" << std::endl;
    for (const TestOutcome &outcome : testOutcomes)
        if (outcome.skipped) {
            std::cout << "\t- " << outcome.name << " : " << outcome.message << std::endl;
            skipped++;
        }
    std::cout << std::endl;

    std::cout << "Failed tests:" << std::endl;
    for (const TestOutcome &outcome : testOutcomes)
        if (!outcome.success && !outcome.skipped) {
            std::cout << "\t- " << outcome.name << " : " << outcome.message << std::endl;
            failed++;
        }
    std::cout << std::endl;

    std::cout << "Results:\n\t- succeded: " << succeded << "\n\t- skipped: " << skipped << "\n\t- failed: " << failed
              << std::endl;
}

void Tester::init() {
    CHIP8::verbose = false;

    opcode_test_arr[0] = &Tester::op_00E0_test_;
    opcode_test_arr[1] = &Tester::op_00EE_test_;
    opcode_test_arr[2] = &Tester::op_0nnn_test_;
    opcode_test_arr[3] = &Tester::op_1nnn_test_;
    opcode_test_arr[4] = &Tester::op_2nnn_test_;
    opcode_test_arr[5] = &Tester::op_3xkk_test_;
    opcode_test_arr[6] = &Tester::op_4xkk_test_;
    opcode_test_arr[7] = &Tester::op_5xy0_test_;
    opcode_test_arr[8] = &Tester::op_6xkk_test_;
    opcode_test_arr[9] = &Tester::op_7xkk_test_;
    opcode_test_arr[10] = &Tester::op_8xy0_test_;
    opcode_test_arr[11] = &Tester::op_8xy1_test_;
    opcode_test_arr[12] = &Tester::op_8xy2_test_;
    opcode_test_arr[13] = &Tester::op_8xy3_test_;
    opcode_test_arr[14] = &Tester::op_8xy4_test_;
    opcode_test_arr[15] = &Tester::op_8xy5_test_;
    opcode_test_arr[16] = &Tester::op_8xy6_test_;
    opcode_test_arr[17] = &Tester::op_8xy7_test_;
    opcode_test_arr[18] = &Tester::op_8xyE_test_;
    opcode_test_arr[19] = &Tester::op_9xy0_test_;
    opcode_test_arr[20] = &Tester::op_Annn_test_;
    opcode_test_arr[21] = &Tester::op_Bnnn_test_;
    opcode_test_arr[22] = &Tester::op_Cxkk_test_;
    opcode_test_arr[23] = &Tester::op_Dxyn_test_;
    opcode_test_arr[24] = &Tester::op_Ex9E_test_;
    opcode_test_arr[25] = &Tester::op_ExA1_test_;
    opcode_test_arr[26] = &Tester::op_Fx07_test_;
    opcode_test_arr[27] = &Tester::op_Fx0A_test_;
    opcode_test_arr[28] = &Tester::op_Fx15_test_;
    opcode_test_arr[29] = &Tester::op_Fx18_test_;
    opcode_test_arr[30] = &Tester::op_Fx1E_test_;
    opcode_test_arr[31] = &Tester::op_Fx29_test_;
    opcode_test_arr[32] = &Tester::op_Fx33_test_;
    opcode_test_arr[33] = &Tester::op_Fx55_test_;
    opcode_test_arr[34] = &Tester::op_Fx65_test_;
}

void Tester::beforeEach() {
    initialize();
}

void Tester::runCurrentOpcode() {
    decode();
    execute();
}

// CLS - clear screen
Tester::TestOutcome Tester::op_00E0_test_() {
    TestOutcome outcome{"00E0", true, false};

    opcode = 0x00E0;
    runCurrentOpcode();

    for (auto pixel : gfx)
        if (pixel != 0) {
            outcome.success = false;
            outcome.message = "The screen is not properly cleared.";
            break;
        }

    return outcome;
}

// RET - return from a subroutine
Tester::TestOutcome Tester::op_00EE_test_() {
    TestOutcome outcome{"00EE", true, false};

    sp = 1;
    stack[0] = 0x270;
    pc = 0x300;
    opcode = 0x00EE;

    runCurrentOpcode();

    if (sp != 0) {
        outcome.success = false;
        outcome.message = "Failed to correctly decrease the stack pointer.";
        return outcome;
    }

    if (pc != 0x270 + 2) {
        outcome.success = false;
        outcome.message = "Failed to set the program counter to the correct value.";
        return outcome;
    }

    return outcome;
}

// SYS addr - execute a machine language subroutine at address nnn (ignored on modern interpreters)
Tester::TestOutcome Tester::op_0nnn_test_() {
    TestOutcome outcome{"0nnn", true, false};

    opcode = 0x0123;
    pc = 0x300;

    runCurrentOpcode();

    if (pc != 0x300 + 2) {
        outcome.success = false;
        outcome.message = "Failed to properly increment the program counter.";
        return outcome;
    }

    return outcome;
}

// JMP addr - jump to address nnn
Tester::TestOutcome Tester::op_1nnn_test_() {
    TestOutcome outcome{"1nnn", true, false};

    opcode = 0x1333;
    pc = 0x200;

    runCurrentOpcode();

    if (pc != 0x333) {
        outcome.success = false;
        outcome.message = "Failed to set the program counter to the correct value.";
        return outcome;
    }

    return outcome;
}

// CALL addr - execute subroutine starting at address nnn
Tester::TestOutcome Tester::op_2nnn_test_() {
    TestOutcome outcome{"2nnn", true, false};

    opcode = 0x2333;
    pc = 0x500;
    sp = 0;

    runCurrentOpcode();

    if (pc != 0x333) {
        outcome.success = false;
        outcome.message = "Failed to set the program counter to the correct value.";
        return outcome;
    }

    if (sp != 1) {
        outcome.success = false;
        outcome.message = "Failed to increment stack pointer.";
        return outcome;
    }

    if (stack[0] != 0x500) {
        outcome.success = false;
        outcome.message = "Failed to push program counter value to stack.";
        return outcome;
    }

    return outcome;
}

// SE Vx, kk - skip the following instruction if  Vx == kk
Tester::TestOutcome Tester::op_3xkk_test_() {
    TestOutcome outcome{"3xkk", true, false};

    opcode = 0x312A;
    pc = 0x300;
    V[1] = 0x2A;

    runCurrentOpcode();

    if (pc != 0x300 + 4) {
        outcome.success = false;
        outcome.message = "Failed to skip the following instruction when equal.";
        return outcome;
    }

    beforeEach();

    opcode = 0x3111;
    pc = 0x400;
    V[1] = 0x10;

    runCurrentOpcode();

    if (pc != 0x400 + 2) {
        outcome.success = false;
        outcome.message = "Failed to not skip the following instruction when not equal.";
        return outcome;
    }

    return outcome;
}

// SNE Vx, kk - skip the following instruction if  Vx != kk
Tester::TestOutcome Tester::op_4xkk_test_() {
    TestOutcome outcome{"4xkk", true, false};
    opcode = 0x412A;
    pc = 0x300;
    V[1] = 0x21;

    runCurrentOpcode();

    if (pc != 0x300 + 4) {
        outcome.success = false;
        outcome.message = "Failed to skip the following instruction when not equal.";
        return outcome;
    }

    beforeEach();

    opcode = 0x4111;
    pc = 0x400;
    V[1] = 0x11;

    runCurrentOpcode();

    if (pc != 0x400 + 2) {
        outcome.success = false;
        outcome.message = "Failed to not skip the following instruction when equal.";
        return outcome;
    }

    return outcome;
}

// SE Vx, Vy - skip the following instruction if  Vx == Vy
Tester::TestOutcome Tester::op_5xy0_test_() {
    TestOutcome outcome{"5xy0", true, false};

    opcode = 0x5020;
    pc = 0x300;
    V[0] = 0x21;
    V[2] = 0x21;

    runCurrentOpcode();

    if (pc != 0x300 + 4) {
        outcome.success = false;
        outcome.message = "Failed to skip the following instruction when registers are equal.";
        return outcome;
    }

    beforeEach();

    opcode = 0x5020;
    pc = 0x300;
    V[0] = 0x20;
    V[2] = 0x21;

    runCurrentOpcode();

    if (pc != 0x300 + 2) {
        outcome.success = false;
        outcome.message = "Failed to not skip the following instruction when registers are not equal.";
        return outcome;
    }

    return outcome;
}

// LD Vx, byte - puts value kk into register Vx
Tester::TestOutcome Tester::op_6xkk_test_() {
    TestOutcome outcome{"6xkk", true, false};

    opcode = 0x6011;
    V[0] = 0x0;
    runCurrentOpcode();

    if (V[0] != 0x11) {
        outcome.success = false;
        outcome.message = "Failed to properly load the value into the register.";
        return outcome;
    }

    return outcome;
}

// ADD Vx, byte - adds value kk to register Vx, stores result in Vx
Tester::TestOutcome Tester::op_7xkk_test_() {
    TestOutcome outcome{"7xkk", true, false};

    opcode = 0x7005;
    V[0] = 0x5;
    runCurrentOpcode();

    if (V[0] != 0xA) {
        outcome.success = false;
        outcome.message = "Failed to properly add the value to the value in register.";
        return outcome;
    }

    return outcome;
}

// LD Vx, Vy - stores the value of register Vy in register Vx
Tester::TestOutcome Tester::op_8xy0_test_() {
    TestOutcome outcome{"8xy0", true, false};

    opcode = 0x8010;
    V[0] = 0x2;
    V[1] = 0x3;
    runCurrentOpcode();

    if (V[0] != 0x3) {
        outcome.success = false;
        outcome.message = "Failed to properly load the value into the register.";
        return outcome;
    }

    return outcome;
}

// OR Vx, Vy - performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx
Tester::TestOutcome Tester::op_8xy1_test_() {
    TestOutcome outcome{"8xy1", true, false};

    opcode = 0x8011;
    V[0] = 0b10110110;
    V[1] = 0b11100000;
    runCurrentOpcode();

    if (V[0] != 0b11110110) {
        outcome.success = false;
        outcome.message = "Failed to properly perform the OR operation.";
        return outcome;
    }

    return outcome;
}

// AND Vx, Vy - performs a bitwise AND on the values of Vx and Vy, then stores the result
Tester::TestOutcome Tester::op_8xy2_test_() {
    TestOutcome outcome{"8xy2", true, false};

    opcode = 0x8012;
    V[0] = 0b10110110;
    V[1] = 0b11100000;
    runCurrentOpcode();

    if (V[0] != 0b10100000) {
        outcome.success = false;
        outcome.message = "Failed to properly perform the AND operation.";
        return outcome;
    }

    return outcome;
}

// XOR Vx, Vy - performs a bitwise XOR on the values of Vx and Vy, then stores the result in Vx
Tester::TestOutcome Tester::op_8xy3_test_() {
    TestOutcome outcome{"8xy3", true, false};

    opcode = 0x8013;
    V[0] = 0b10110110;
    V[1] = 0b11100000;
    runCurrentOpcode();

    if (V[0] != 0b01010110) {
        outcome.success = false;
        outcome.message = "Failed to properly perform the XOR operation.";
        return outcome;
    }

    return outcome;
}

// ADD Vx, Vy - adds Vx to Vy, stores the lowest 8 bits of the result in Vx, set VF = carry
Tester::TestOutcome Tester::op_8xy4_test_() {
    TestOutcome outcome{"8xy4", true, false};

    opcode = 0x8014;
    V[0] = 0x1;
    V[1] = 0x1;
    V[0xF] = 0;
    runCurrentOpcode();

    if (V[0] != 0x2) {
        outcome.success = false;
        outcome.message = "Failed to properly add the values.";
        return outcome;
    }

    if (V[0xF] != 0) {
        outcome.success = false;
        outcome.message = "Set the carry flag despite lack of overflow.";
        return outcome;
    }

    beforeEach();

    opcode = 0x8014;
    V[0] = 0xFF;
    V[1] = 0xA;
    V[0xF] = 0;
    runCurrentOpcode();

    if (V[0] != 0x9) {
        outcome.success = false;
        outcome.message = "Failed to properly add the values (with overflow).";
        return outcome;
    }

    if (V[0xF] != 1) {
        outcome.success = false;
        outcome.message = "Unset the carry flag despite overflow.";
        return outcome;
    }

    return outcome;
}

// SUB Vx, Vy - sets VF to 1 if Vx > Vy else to 0, subtracts Vy from Vx, stores result in Vx
Tester::TestOutcome Tester::op_8xy5_test_() {
    TestOutcome outcome{"8xy5", true, false};

    opcode = 0x8015;
    V[0] = 0x9;
    V[1] = 0x5;
    V[0xF] = 0;
    runCurrentOpcode();

    if (V[0] != 0x4) {
        outcome.success = false;
        outcome.message = "Failed to properly subtract the values.";
        return outcome;
    }

    if (V[0xF] != 1) {
        outcome.success = false;
        outcome.message = "Unsets the carry flag despite lack of underflow.";
        return outcome;
    }

    beforeEach();

    opcode = 0x8015;
    V[0] = 0x5;
    V[1] = 0x6;
    V[0xF] = 0;
    runCurrentOpcode();

    if (V[0] != 0xFF) {
        outcome.success = false;
        outcome.message = "Failed to properly subtract the values (with underflow).";
        return outcome;
    }

    if (V[0xF] != 0) {
        outcome.success = false;
        outcome.message = "Sets the carry flag despite underflow.";
        return outcome;
    }

    return outcome;
}


// SHR Vx, Vy - stores the value of register Vy shifted right one bit in register Vx, sets register VF to the least significant bit prior to the shift
Tester::TestOutcome Tester::op_8xy6_test_() {
    TestOutcome outcome{"8xy6", true, false};

    opcode = 0x8016;
    V[0] = 0;
    V[1] = 0b11110101;
    V[0xF] = 0;

    runCurrentOpcode();

    if (V[0] != 0b01111010) {
        outcome.success = false;
        outcome.message = "Failed to properly shift the value right.";
        return outcome;
    }

    if (V[0xF] != 1) {
        outcome.success = false;
        outcome.message = "Failed to properly set the carry flag.";
        return outcome;
    }

    return outcome;
}

// SUBN Vx, Vy - sets VF to 1 if Vy > Vx else to 0, subtracts Vx from Vy, stores result in Vx
Tester::TestOutcome Tester::op_8xy7_test_() {
    TestOutcome outcome{"8xy7", true, false};

    opcode = 0x8017;
    V[0] = 0x9;
    V[1] = 0x8;
    V[0xF] = 0;
    runCurrentOpcode();

    if (V[0] != 0xFF) {
        outcome.success = false;
        outcome.message = "Failed to properly subtract the values (with underflow).";
        return outcome;
    }

    if (V[0xF] != 0) {
        outcome.success = false;
        outcome.message = "Sets the carry flag despite the underflow.";
        return outcome;
    }

    beforeEach();

    opcode = 0x8017;
    V[0] = 0x5;
    V[1] = 0x6;
    V[0xF] = 0;
    runCurrentOpcode();

    if (V[0] != 0x1) {
        outcome.success = false;
        outcome.message = "Failed to properly subtract the values.";
        return outcome;
    }

    if (V[0xF] != 1) {
        outcome.success = false;
        outcome.message = "Unsets the carry flag despite the lack underflow.";
        return outcome;
    }

    return outcome;
}

// SHL Vx, Vy - stores the value of register Vy shifted left one bit in register Vx, sets register VF to the most significant bit prior to the shift
Tester::TestOutcome Tester::op_8xyE_test_() {
    TestOutcome outcome{"8xyE", true, false};

    opcode = 0x801E;
    V[0] = 0;
    V[1] = 0b11110101;
    V[0xF] = 0;

    runCurrentOpcode();

    if (V[0] != 0b11101010) {
        outcome.success = false;
        outcome.message = "Failed to properly shift the value left.";
        return outcome;
    }

    if (V[0xF] != 1) {
        outcome.success = false;
        outcome.message = "Failed to properly set the carry flag.";
        return outcome;
    }

    return outcome;
}

// SNE Vx, Vy - skips next instruction if Vx != Vy
Tester::TestOutcome Tester::op_9xy0_test_() {
    TestOutcome outcome{"9xy0", true, false};

    opcode = 0x9010;
    pc = 0x300;
    V[0] = 0x21;
    V[1] = 0x21;

    runCurrentOpcode();

    if (pc != 0x300 + 2) {
        outcome.success = false;
        outcome.message = "Failed to not skip the following instruction when registers are equal.";
        return outcome;
    }

    beforeEach();

    opcode = 0x9010;
    pc = 0x300;
    V[0] = 0x20;
    V[1] = 0x21;

    runCurrentOpcode();

    if (pc != 0x300 + 4) {
        outcome.success = false;
        outcome.message = "Failed to skip the following instruction when registers are not equal.";
        return outcome;
    }

    return outcome;
}

// LD I, addr - sets register I to nnn
Tester::TestOutcome Tester::op_Annn_test_() {
    TestOutcome outcome{"Annn", true, false};

    opcode = 0xA123;
    I = 0x000;
    runCurrentOpcode();

    if (I != 0x123) {
        outcome.success = false;
        outcome.message = "Failed to load a correct value into the I register.";
        return outcome;
    }

    return outcome;
}

// JMP V0, addr - jump to location nnn + V0
Tester::TestOutcome Tester::op_Bnnn_test_() {
    TestOutcome outcome{"Bnnn", true, false};

    opcode = 0xB333;
    pc = 0x200;
    V[0] = 0x1B;

    runCurrentOpcode();

    if (pc != 0x333 + 0x1B) {
        outcome.success = false;
        outcome.message = "Failed to jump to the correct address.";
        return outcome;
    }

    return outcome;
}

// RND Vx, byte - sets Vx to a random byte ANDed with kk
Tester::TestOutcome Tester::op_Cxkk_test_() {
    TestOutcome outcome{"Cxkk", true, false};

    opcode = 0xC00F;
    V[0] = 0xFF;

    runCurrentOpcode();

    if (!(V[0] >= 0 && V[0] <= 0xF)) {
        outcome.success = false;
        outcome.message = "Failed to generate a random number with correct mask.";
        return outcome;
    }

    return outcome;
}

// DRW Vx, Vy, N - draws a sprite at position Vx, Vy with N bytes of sprite data starting at address stored in I, sets VF if any pixel is unset
Tester::TestOutcome Tester::op_Dxyn_test_() {
    TestOutcome outcome{"Dxyn", true, false};

    opcode = 0xD011;
    I = 0x400;
    V[0] = 5;
    V[1] = 0;
    V[0xF] = 0;
    memory[0x400] = 0b10101010;

    runCurrentOpcode();

    unsigned char expected_gfx[Spec::DISPLAY_SIZE];
    for (unsigned char &i : expected_gfx) {
        i = 0;
    }

    expected_gfx[5] = 1;
    expected_gfx[6] = 0;
    expected_gfx[7] = 1;
    expected_gfx[8] = 0;
    expected_gfx[9] = 1;
    expected_gfx[10] = 0;
    expected_gfx[11] = 1;
    expected_gfx[12] = 0;

    bool discrepancyDetected = false;
    for (int i = 0; i < Spec::DISPLAY_SIZE; i++)
        if (gfx[i] != expected_gfx[i]) {
            discrepancyDetected = true;
            break;
        }

    if (discrepancyDetected) {
        outcome.success = false;
        outcome.message = "Failed to correctly draw the sprite.";
        return outcome;
    }

    if (V[0xF] != 0) {
        outcome.success = false;
        outcome.message = "Incorrectly set the carry flag (VF) despite lack of collision.";
        return outcome;
    }

    runCurrentOpcode();

    for (unsigned char &i : expected_gfx) {
        i = 0;
    }

    discrepancyDetected = false;
    for (int i = 0; i < Spec::DISPLAY_SIZE; i++)
        if (gfx[i] != expected_gfx[i]) {
            discrepancyDetected = true;
            break;
        }

    if (discrepancyDetected) {
        outcome.success = false;
        outcome.message = "Failed to correctly draw the sprite on top of an already drawn one.";
        return outcome;
    }

    if (V[0xF] != 1) {
        outcome.success = false;
        outcome.message = "Failed to set the carry flag (VF) despite the collision.";
        return outcome;
    }

    return outcome;
}

// SKP Vx - skips next instruction if key with the value of Vx is pressed
Tester::TestOutcome Tester::op_Ex9E_test_() {
    TestOutcome outcome{"Ex9E", true, false};

    opcode = 0xE09E;
    pc = 0x300;
    V[0] = 0xB;
    keyboard[0xB] = 0xFF;

    runCurrentOpcode();

    if (pc != 0x300 + 4) {
        outcome.success = false;
        outcome.message = "Failed to correctly skip the fo;lowing instruction on key press.";
        return outcome;
    }

    opcode = 0xE09E;
    pc = 0x300;
    V[0] = 0xB;
    keyboard[0xB] = 0;

    runCurrentOpcode();

    if (pc != 0x300 + 2) {
        outcome.success = false;
        outcome.message = "Skipped the instruction despite the key not being pressed.";
        return outcome;
    }

    return outcome;
}

// SKNP Vx - skips next instruction if key with the value of Vx is not pressed
Tester::TestOutcome Tester::op_ExA1_test_() {
    TestOutcome outcome{"ExA1", true, false};

    opcode = 0xE0A1;
    pc = 0x300;
    V[0] = 0xB;
    keyboard[0xB] = 0;

    runCurrentOpcode();

    if (pc != 0x300 + 4) {
        outcome.success = false;
        outcome.message = "Failed to correctly skip the following instruction despite the not being pressed.";
        return outcome;
    }

    opcode = 0xE0A1;
    pc = 0x300;
    V[0] = 0xB;
    keyboard[0xB] = 0xFF;

    runCurrentOpcode();

    if (pc != 0x300 + 2) {
        outcome.success = false;
        outcome.message = "Skipped the instruction despite the key being pressed.";
        return outcome;
    }

    return outcome;
}

// LD Vx, DT - stores the current delay timer value in Vx
Tester::TestOutcome Tester::op_Fx07_test_() {
    TestOutcome outcome{"Fx07", true, false};

    opcode = 0xF507;
    delayTimer = 0x1F;
    V[5] = 0;

    runCurrentOpcode();

    if (V[5] != 0x1F) {
        outcome.success = false;
        outcome.message = "Failed to load the current delay timer value into the register.";
        return outcome;
    }

    return outcome;
}

// LD Vx, K - waits for a key press, stores the value of key press in Vx
Tester::TestOutcome Tester::op_Fx0A_test_() {
    TestOutcome outcome{"Fx0A", false, true,
                        "Requires manual testing."};
    return outcome;
}

// LD DT, Vx - sets the delay timer to value from Vx
Tester::TestOutcome Tester::op_Fx15_test_() {
    TestOutcome outcome{"Fx15", true, false};

    opcode = 0xF515;
    delayTimer = 0;
    V[5] = 0x2F;

    runCurrentOpcode();

    if (delayTimer != 0x2F) {
        outcome.success = false;
        outcome.message = "Failed to load the register value into the delay timer.";
        return outcome;
    }

    return outcome;
}

// LD ST, Vx - sets the sound timer to value from Vx
Tester::TestOutcome Tester::op_Fx18_test_() {
    TestOutcome outcome{"Fx18", true, false};

    opcode = 0xF518;
    delayTimer = 0;
    V[5] = 0x2F;

    runCurrentOpcode();

    if (soundTimer != 0x2F) {
        outcome.success = false;
        outcome.message = "Failed to load the register value into the sound timer.";
        return outcome;
    }

    return outcome;
}

// ADD I, Vx - adds Vx to I, stores result in I
Tester::TestOutcome Tester::op_Fx1E_test_() {
    TestOutcome outcome{"Fx1E", true, false};

    opcode = 0xF21E;
    I = 0x300;
    V[2] = 0xAF;

    runCurrentOpcode();

    if (I != 0x300 + 0xAF) {
        outcome.success = false;
        outcome.message = "Failed to correctly add the register value to I register.";
        return outcome;
    }

    return outcome;
}

Tester::TestOutcome Tester::op_Fx29_test_() {
    TestOutcome outcome{"Fx29", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx33_test_() {
    TestOutcome outcome{"Fx33", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx55_test_() {
    TestOutcome outcome{"Fx55", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx65_test_() {
    TestOutcome outcome{"Fx65", false, true};

    return outcome;
}
