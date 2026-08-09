#include <TestUtils.h>
#include <gtest/gtest.h>
#include "Emulator.h"

using RegistersSetter = void(Registers::*)(u16 value);
using RegistersGetter = u16(Registers::*)();

struct Inc16TestParameters {
    std::string name;
    u8 instruction;
    u16 initialValue;
    u8 initialFlags;
    u16 expectedValue;
    u8 expectedFlags;
    RegistersSetter initialValueSetter;
    RegistersGetter resultGetter;
};

class Inc16Test : public ::testing::TestWithParam<Inc16TestParameters> {
protected:
    Emulator* emulator = TestUtils::getEmulator();

    void TearDown() override {
        delete emulator;
    }
};

TEST_P(Inc16Test, Increment) {
    const auto& param = GetParam();
    (emulator->cpu.registers.*param.initialValueSetter)(param.initialValue);
    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();
    EXPECT_EQ((emulator->cpu.registers.*param.resultGetter)(), param.expectedValue);
}

TEST_P(Inc16Test, ActiveFlags) {
    const auto& param = GetParam();
    (emulator->cpu.registers.*param.initialValueSetter)(param.initialValue);
    emulator->cpu.registers.setF(param.initialFlags);
    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();
    EXPECT_EQ(emulator->cpu.registers.getF(), param.expectedFlags);
}

INSTANTIATE_TEST_SUITE_P(
    INC,
    Inc16Test,
    ::testing::Values(
        Inc16TestParameters{"INC_BC", 0x03, 0x27, 0, 0x28, 0, &Registers::setBC, &Registers::getBC},
        Inc16TestParameters{"INC_DE", 0x13, 0x27, 0, 0x28, 0, &Registers::setDE, &Registers::getDE},
        Inc16TestParameters{"INC_HL", 0x23, 0x27, 0, 0x28, 0, &Registers::setHL, &Registers::getHL},
        Inc16TestParameters{"INC_SP", 0x33, 0x27, 0, 0x28, 0, &Registers::setSP, &Registers::getSP},

        Inc16TestParameters{"INC_BC_NibbleOverflow", 0x03, 0x0F, 0, 0x10, 0, &Registers::setBC, &Registers::getBC},
        Inc16TestParameters{"INC_DE_NibbleOverflow", 0x13, 0x0F, 0, 0x10, 0, &Registers::setDE, &Registers::getDE},
        Inc16TestParameters{"INC_HL_NibbleOverflow", 0x23, 0x0F, 0, 0x10, 0, &Registers::setHL, &Registers::getHL},
        Inc16TestParameters{"INC_SP_NibbleOverflow", 0x33, 0x0F, 0, 0x10, 0, &Registers::setSP, &Registers::getSP},

        Inc16TestParameters{"INC_BC_ByteOverflow", 0x03, 0xFF, 0, 0x100, 0, &Registers::setBC, &Registers::getBC},
        Inc16TestParameters{"INC_DE_ByteOverflow", 0x13, 0xFF, 0, 0x100, 0, &Registers::setDE, &Registers::getDE},
        Inc16TestParameters{"INC_HL_ByteOverflow", 0x23, 0xFF, 0, 0x100, 0, &Registers::setHL, &Registers::getHL},
        Inc16TestParameters{"INC_SP_ByteOverflow", 0x33, 0xFF, 0, 0x100, 0, &Registers::setSP, &Registers::getSP},

        Inc16TestParameters{"INC_BC_UnalteredCarryFlag", 0x03, 0xFF, C_FLAG, 0x100, C_FLAG, &Registers::setBC, &Registers::getBC},
        Inc16TestParameters{"INC_DE_UnalteredCarryFlag", 0x13, 0xFF, C_FLAG, 0x100, C_FLAG, &Registers::setDE, &Registers::getDE},
        Inc16TestParameters{"INC_HL_UnalteredCarryFlag", 0x23, 0xFF, C_FLAG, 0x100, C_FLAG, &Registers::setHL, &Registers::getHL},
        Inc16TestParameters{"INC_SP_UnalteredCarryFlag", 0x33, 0xFF, C_FLAG, 0x100, C_FLAG, &Registers::setSP, &Registers::getSP}
    ),
    [](const ::testing::TestParamInfo<Inc16TestParameters>& info) { return info.param.name; }
);