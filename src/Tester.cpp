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

    std::cout << "Succeded: " << succeded << " Skipped: " << skipped << " Failed: " << failed << std::endl;
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
    CHIP8::opcode = 0x00E0;

    runCurrentOpcode();
    TestOutcome outcome{"00E0", true, false};

    for (auto pixel : CHIP8::gfx)
        if (pixel != 0) {
            outcome.success = false;
            outcome.message = "The screen is not properly cleared.";
            break;
        }

    return outcome;
}

Tester::TestOutcome Tester::op_00EE_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"00EE", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_0nnn_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"0nnn", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_1nnn_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"1nnn", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_2nnn_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"2nnn", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_3xkk_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"3xkk", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_4xkk_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"4xkk", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_5xy0_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"5xy0", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_6xkk_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"6xkk", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_7xkk_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"7xkk", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_8xy0_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"8xy0", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_8xy1_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"8xy1", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_8xy2_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"8xy2", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_8xy3_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"8xy3", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_8xy4_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"8xy4", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_8xy5_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"8xy5", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_8xy6_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"8xy6", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_8xy7_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"8xy7", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_8xyE_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"8xyE", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_9xy0_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"9xy0", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Annn_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Annn", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Bnnn_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Bnnn", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Cxkk_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Cxkk", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Dxyn_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Dxyn", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Ex9E_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Ex9E", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_ExA1_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"ExA1", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx07_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Fx07", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx0A_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Fx0A", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx15_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Fx15", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx18_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Fx18", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx1E_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Fx1E", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx29_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Fx29", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx33_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Fx33", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx55_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Fx55", false, true};

    return outcome;
}

Tester::TestOutcome Tester::op_Fx65_test_() {
    runCurrentOpcode();
    TestOutcome outcome{"Fx65", false, true};

    return outcome;
}
