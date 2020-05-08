//
// Created by Krzysiek on 08.05.2020.
//

#include "Tester.hpp"

void Tester::runTests() {

    TestOutcome testOutcomes[35];

    for (int i = 0; i < 35; i++) {
        beforeEach();
        testOutcomes[i] = (this->*opcode_test_arr[i])();
    }
}

void Tester::init() {
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

Tester::TestOutcome Tester::op_00E0_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_00EE_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_0nnn_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_1nnn_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_2nnn_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_3xkk_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_4xkk_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_5xy0_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_6xkk_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_7xkk_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_8xy0_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_8xy1_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_8xy2_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_8xy3_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_8xy4_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_8xy5_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_8xy6_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_8xy7_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_8xyE_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_9xy0_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Annn_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Bnnn_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Cxkk_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Dxyn_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Ex9E_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_ExA1_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Fx07_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Fx0A_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Fx15_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Fx18_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Fx1E_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Fx29_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Fx33_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Fx55_test_() {
    return Tester::TestOutcome();
}

Tester::TestOutcome Tester::op_Fx65_test_() {
    return Tester::TestOutcome();
}
