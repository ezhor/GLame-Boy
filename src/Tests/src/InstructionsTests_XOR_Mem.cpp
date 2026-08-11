#include <TestUtils.h>
#include <gtest/gtest.h>
#include "Emulator.h"

struct XorMemTestParameters {
    std::string name;
    u8 instruction;
    u8 a;
    u8 b;
    u8 expectedResult;
    u8 expectedFlags;
    u16 memoryLocation;
};

class XorMemTest : public ::testing::TestWithParam<XorMemTestParameters> {
protected:
    Emulator* emulator = TestUtils::getEmulator();

    void TearDown() override {
        delete emulator;
    }
};

TEST_P(XorMemTest, XOR) {
    const auto& param = GetParam();
    emulator->cpu.registers.setA(param.a);
    emulator->cpu.registers.setHL(param.memoryLocation);
    emulator->bus.write(param.memoryLocation, param.b);

    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();

    EXPECT_EQ(emulator->cpu.registers.getA(), param.expectedResult);
}

TEST_P(XorMemTest, Flags) {
    const auto& param = GetParam();
    emulator->cpu.registers.setA(param.a);
    emulator->cpu.registers.setHL(param.memoryLocation);
    emulator->bus.write(param.memoryLocation, param.b);

    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();

    EXPECT_EQ(emulator->cpu.registers.getF(), param.expectedFlags);
}

INSTANTIATE_TEST_SUITE_P(
    XOR,
    XorMemTest,
    ::testing::Values(
        XorMemTestParameters{"XOR_Mem_HL_OR", 0xAE, 0b01010101, 0b10101010, 0b11111111, NO_FLAG, 0x2727},
        XorMemTestParameters{"XOR_d8_OR", 0xEE, 0b01010101, 0b10101010, 0b11111111, NO_FLAG, INITIAL_PROGRAM_COUNTER + 1},

        XorMemTestParameters{"XOR_Mem_HL_Excluding", 0xAE, 0b00001111, 0b11111111, 0b11110000, NO_FLAG, 0x2727},
        XorMemTestParameters{"XOR_d8_Excluding", 0xEE, 0b00001111, 0b11111111, 0b11110000, NO_FLAG, INITIAL_PROGRAM_COUNTER + 1},

        XorMemTestParameters{"XOR_Mem_HL_ZeroFlag", 0xAE, 0b00001111, 0b00001111, 0, Z_FLAG, 0x2727},
        XorMemTestParameters{"XOR_d8_ZeroFlag", 0xEE, 0b00001111, 0b00001111, 0, Z_FLAG, INITIAL_PROGRAM_COUNTER + 1}
    ),
    [](const ::testing::TestParamInfo<XorMemTestParameters>& info) { return info.param.name; }
);