//
// Created by Krzysiek on 08.05.2020.
//

#ifndef PROJEKT_INDYWIDUALNY_TESTER_H
#define PROJEKT_INDYWIDUALNY_TESTER_H


#include "CHIP8.hpp"

class Tester {
    CHIP8 * chip = nullptr;

    TestOutcome (Tester::*opcode_test_arr[35])();

    struct TestOutcome {
        char * name;
        bool success;
        char * message;
    };

public:
    void initialize();
    void runTests();

private:
    void beforeEach();

    void runCurrentOpcode();

    TestOutcome op_00E0_test_();

    TestOutcome op_00EE_test_();

    TestOutcome op_0nnn_test_();

    TestOutcome op_1nnn_test_();

    TestOutcome op_2nnn_test_();

    TestOutcome op_3xkk_test_();

    TestOutcome op_4xkk_test_();

    TestOutcome op_5xy0_test_();

    TestOutcome op_6xkk_test_();

    TestOutcome op_7xkk_test_();

    TestOutcome op_8xy0_test_();

    TestOutcome op_8xy1_test_();

    TestOutcome op_8xy2_test_();

    TestOutcome op_8xy3_test_();

    TestOutcome op_8xy4_test_();

    TestOutcome op_8xy5_test_();

    TestOutcome op_8xy6_test_();

    TestOutcome op_8xy7_test_();

    TestOutcome op_8xyE_test_();

    TestOutcome op_9xy0_test_();

    TestOutcome op_Annn_test_();

    TestOutcome op_Bnnn_test_();

    TestOutcome op_Cxkk_test_();

    TestOutcome op_Dxyn_test_();

    TestOutcome op_Ex9E_test_();

    TestOutcome op_ExA1_test_();

    TestOutcome op_Fx07_test_();

    TestOutcome op_Fx0A_test_();

    TestOutcome op_Fx15_test_();

    TestOutcome op_Fx18_test_();

    TestOutcome op_Fx1E_test_();

    TestOutcome op_Fx29_test_();

    TestOutcome op_Fx33_test_();

    TestOutcome op_Fx55_test_();

    TestOutcome op_Fx65_test_();
};


#endif //PROJEKT_INDYWIDUALNY_TESTER_H
