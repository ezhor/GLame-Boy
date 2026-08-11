#include <TestUtils.h>
#include <gtest/gtest.h>
#include "Emulator.h"

using RegistersSetter = void(Registers::*)(u8 value);

struct XorTestParameters {
    std::string name;
    u8 instruction;
    u8 a;
    u8 b;
    u8 expectedResult;
    u8 expectedFlags;
    RegistersSetter setter;
};

class XorTest : public ::testing::TestWithParam<XorTestParameters> {
protected:
    Emulator* emulator = TestUtils::getEmulator();

    void TearDown() override {
        delete emulator;
    }
};

TEST_P(XorTest, XOR) {
    const auto& param = GetParam();
    emulator->cpu.registers.setA(param.a);
    (emulator->cpu.registers.*param.setter)(param.b);

    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();

    EXPECT_EQ(emulator->cpu.registers.getA(), param.expectedResult);
}

TEST_P(XorTest, Flags) {
    const auto& param = GetParam();
    emulator->cpu.registers.setA(param.a);
    (emulator->cpu.registers.*param.setter)(param.b);

    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();

    EXPECT_EQ(emulator->cpu.registers.getF(), param.expectedFlags);
}

INSTANTIATE_TEST_SUITE_P(
    XOR,
    XorTest,
    ::testing::Values(
        XorTestParameters{"XOR_B_OR", 0xA8, 0b01010101, 0b10101010, 0b11111111, NO_FLAG, &Registers::setB},
        XorTestParameters{"XOR_C_OR", 0xA9, 0b01010101, 0b10101010, 0b11111111, NO_FLAG, &Registers::setC},
        XorTestParameters{"XOR_D_OR", 0xAA, 0b01010101, 0b10101010, 0b11111111, NO_FLAG, &Registers::setD},
        XorTestParameters{"XOR_E_OR", 0xAB, 0b01010101, 0b10101010, 0b11111111, NO_FLAG, &Registers::setE},
        XorTestParameters{"XOR_H_OR", 0xAC, 0b01010101, 0b10101010, 0b11111111, NO_FLAG, &Registers::setH},
        XorTestParameters{"XOR_L_OR", 0xAD, 0b01010101, 0b10101010, 0b11111111, NO_FLAG, &Registers::setL},
        XorTestParameters{"XOR_A_OR", 0xAF, 0b01010101, 0b10101010, 0, Z_FLAG, &Registers::setA},

        XorTestParameters{"XOR_B_Excluding", 0xA8, 0b00001111, 0b11111111, 0b11110000, NO_FLAG, &Registers::setB},
        XorTestParameters{"XOR_C_Excluding", 0xA9, 0b00001111, 0b11111111, 0b11110000, NO_FLAG, &Registers::setC},
        XorTestParameters{"XOR_D_Excluding", 0xAA, 0b00001111, 0b11111111, 0b11110000, NO_FLAG, &Registers::setD},
        XorTestParameters{"XOR_E_Excluding", 0xAB, 0b00001111, 0b11111111, 0b11110000, NO_FLAG, &Registers::setE},
        XorTestParameters{"XOR_H_Excluding", 0xAC, 0b00001111, 0b11111111, 0b11110000, NO_FLAG, &Registers::setH},
        XorTestParameters{"XOR_L_Excluding", 0xAD, 0b00001111, 0b11111111, 0b11110000, NO_FLAG, &Registers::setL},
        XorTestParameters{"XOR_A_Excluding", 0xAF, 0b00001111, 0b11111111, 0, Z_FLAG, &Registers::setA},

        XorTestParameters{"XOR_B_ZeroFlag", 0xA8, 0b00001111, 0b00001111, 0, Z_FLAG, &Registers::setB},
        XorTestParameters{"XOR_C_ZeroFlag", 0xA9, 0b00001111, 0b00001111, 0, Z_FLAG, &Registers::setC},
        XorTestParameters{"XOR_D_ZeroFlag", 0xAA, 0b00001111, 0b00001111, 0, Z_FLAG, &Registers::setD},
        XorTestParameters{"XOR_E_ZeroFlag", 0xAB, 0b00001111, 0b00001111, 0, Z_FLAG, &Registers::setE},
        XorTestParameters{"XOR_H_ZeroFlag", 0xAC, 0b00001111, 0b00001111, 0, Z_FLAG, &Registers::setH},
        XorTestParameters{"XOR_L_ZeroFlag", 0xAD, 0b00001111, 0b00001111, 0, Z_FLAG, &Registers::setL},
        XorTestParameters{"XOR_A_ZeroFlag", 0xAF, 0b00001111, 0b00001111, 0, Z_FLAG, &Registers::setA}
    ),
    [](const ::testing::TestParamInfo<XorTestParameters>& info) { return info.param.name; }
);