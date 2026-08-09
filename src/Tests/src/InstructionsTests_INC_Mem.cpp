#include <TestUtils.h>
#include <gtest/gtest.h>
#include "Emulator.h"

struct IncMemHLTestParameters {
    std::string name;
    u8 instruction;
    u8 initialValue;
    u8 initialFlags;
    u8 expectedValue;
    u8 expectedFlags;
};

class IncMemHLTest : public ::testing::TestWithParam<IncMemHLTestParameters> {
protected:
    Emulator* emulator = TestUtils::getEmulator();

    void TearDown() override {
        delete emulator;
    }
};

TEST_P(IncMemHLTest, Increment) {
    const auto& param = GetParam();
    u16 memoryLocation = 0x2727;
    emulator->bus.write(memoryLocation, param.initialValue);
    emulator->cpu.registers.setHL(memoryLocation);
    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();
    EXPECT_EQ(emulator->bus.read(memoryLocation), param.expectedValue);
}

TEST_P(IncMemHLTest, ActiveFlags) {
    const auto& param = GetParam();
    u16 memoryLocation = 0x2727;
    emulator->bus.write(memoryLocation, param.initialValue);
    emulator->cpu.registers.setHL(memoryLocation);
    emulator->cpu.registers.setF(param.initialFlags);
    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();
    EXPECT_EQ(emulator->cpu.registers.getF(), param.expectedFlags);
}

INSTANTIATE_TEST_SUITE_P(
    INC,
    IncMemHLTest,
    ::testing::Values(
        IncMemHLTestParameters{"INC_mem_HL", 0x34, 0x27, 0, 0x28, 0},
        IncMemHLTestParameters{"INC_mem_HL_NibbleOverflow", 0x34, 0x0F, 0, 0x10, H_FLAG},
        IncMemHLTestParameters{"INC_mem_HL_ByteOverflow", 0x34, 0xFF, 0, 0x00, Z_FLAG | H_FLAG},
        IncMemHLTestParameters{"INC_mem_HL_UnalteredCarryFlag", 0x34, 0xFF, C_FLAG, 0x00, Z_FLAG | H_FLAG | C_FLAG}
    ),
    [](const ::testing::TestParamInfo<IncMemHLTestParameters>& info) { return info.param.name; }
);