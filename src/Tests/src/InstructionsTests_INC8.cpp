#include <TestUtils.h>
#include <gtest/gtest.h>
#include "Emulator.h"

using RegistersSetter = void(Registers::*)(u8 value);
using RegistersGetter = u8(Registers::*)();

struct Inc8TestParameters {
    std::string name;
    u8 instruction;
    u8 initialValue;
    u8 initialFlags;
    u8 expectedValue;
    u8 expectedFlags;
    RegistersSetter initialValueSetter;
    RegistersGetter resultGetter;
};

class Inc8Test : public ::testing::TestWithParam<Inc8TestParameters> {
protected:
    Emulator* emulator = TestUtils::getEmulator();

    void TearDown() override {
        delete emulator;
    }
};

TEST_P(Inc8Test, Increment) {
    const auto& param = GetParam();
    (emulator->cpu.registers.*param.initialValueSetter)(param.initialValue);
    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();
    EXPECT_EQ((emulator->cpu.registers.*param.resultGetter)(), param.expectedValue);
}

TEST_P(Inc8Test, ActiveFlags) {
    const auto& param = GetParam();
    (emulator->cpu.registers.*param.initialValueSetter)(param.initialValue);
    emulator->cpu.registers.setF(param.initialFlags);
    emulator->bus.write(INITIAL_PROGRAM_COUNTER, param.instruction);
    emulator->cpu.tick();
    EXPECT_EQ(emulator->cpu.registers.getF(), param.expectedFlags);
}

INSTANTIATE_TEST_SUITE_P(
    INC,
    Inc8Test,
    ::testing::Values(
        Inc8TestParameters{"INC_B", 0x04, 0x27, 0, 0x28, 0, &Registers::setB, &Registers::getB},
        Inc8TestParameters{"INC_C", 0x0C, 0x27, 0, 0x28, 0, &Registers::setC, &Registers::getC},
        Inc8TestParameters{"INC_D", 0x14, 0x27, 0, 0x28, 0, &Registers::setD, &Registers::getD},
        Inc8TestParameters{"INC_E", 0x1C, 0x27, 0, 0x28, 0, &Registers::setE, &Registers::getE},
        Inc8TestParameters{"INC_H", 0x24, 0x27, 0, 0x28, 0, &Registers::setH, &Registers::getH},
        Inc8TestParameters{"INC_L", 0x2C, 0x27, 0, 0x28, 0, &Registers::setL, &Registers::getL},
        Inc8TestParameters{"INC_A", 0x3C, 0x27, 0, 0x28, 0, &Registers::setA, &Registers::getA},

        Inc8TestParameters{"INC_B_NibbleOverflow", 0x04, 0x0F, 0, 0x10, H_FLAG, &Registers::setB, &Registers::getB},
        Inc8TestParameters{"INC_C_NibbleOverflow", 0x0C, 0x0F, 0, 0x10, H_FLAG, &Registers::setC, &Registers::getC},
        Inc8TestParameters{"INC_D_NibbleOverflow", 0x14, 0x0F, 0, 0x10, H_FLAG, &Registers::setD, &Registers::getD},
        Inc8TestParameters{"INC_E_NibbleOverflow", 0x1C, 0x0F, 0, 0x10, H_FLAG, &Registers::setE, &Registers::getE},
        Inc8TestParameters{"INC_H_NibbleOverflow", 0x24, 0x0F, 0, 0x10, H_FLAG, &Registers::setH, &Registers::getH},
        Inc8TestParameters{"INC_L_NibbleOverflow", 0x2C, 0x0F, 0, 0x10, H_FLAG, &Registers::setL, &Registers::getL},

        Inc8TestParameters{"INC_B_ByteOverflow", 0x04, 0xFF, 0, 0x00, Z_FLAG | H_FLAG, &Registers::setB, &Registers::getB},
        Inc8TestParameters{"INC_C_ByteOverflow", 0x0C, 0xFF, 0, 0x00, Z_FLAG | H_FLAG, &Registers::setC, &Registers::getC},
        Inc8TestParameters{"INC_D_ByteOverflow", 0x14, 0xFF, 0, 0x00, Z_FLAG | H_FLAG, &Registers::setD, &Registers::getD},
        Inc8TestParameters{"INC_E_ByteOverflow", 0x1C, 0xFF, 0, 0x00, Z_FLAG | H_FLAG, &Registers::setE, &Registers::getE},
        Inc8TestParameters{"INC_H_ByteOverflow", 0x24, 0xFF, 0, 0x00, Z_FLAG | H_FLAG, &Registers::setH, &Registers::getH},
        Inc8TestParameters{"INC_L_ByteOverflow", 0x2C, 0xFF, 0, 0x00, Z_FLAG | H_FLAG, &Registers::setL, &Registers::getL},

        Inc8TestParameters{"INC_B_UnalteredCarryFlag", 0x04, 0xFF, C_FLAG, 0x00, Z_FLAG | H_FLAG | C_FLAG, &Registers::setB, &Registers::getB},
        Inc8TestParameters{"INC_C_UnalteredCarryFlag", 0x0C, 0xFF, C_FLAG, 0x00, Z_FLAG | H_FLAG | C_FLAG, &Registers::setC, &Registers::getC},
        Inc8TestParameters{"INC_D_UnalteredCarryFlag", 0x14, 0xFF, C_FLAG, 0x00, Z_FLAG | H_FLAG | C_FLAG, &Registers::setD, &Registers::getD},
        Inc8TestParameters{"INC_E_UnalteredCarryFlag", 0x1C, 0xFF, C_FLAG, 0x00, Z_FLAG | H_FLAG | C_FLAG, &Registers::setE, &Registers::getE},
        Inc8TestParameters{"INC_H_UnalteredCarryFlag", 0x24, 0xFF, C_FLAG, 0x00, Z_FLAG | H_FLAG | C_FLAG, &Registers::setH, &Registers::getH},
        Inc8TestParameters{"INC_L_UnalteredCarryFlag", 0x2C, 0xFF, C_FLAG, 0x00, Z_FLAG | H_FLAG | C_FLAG, &Registers::setL, &Registers::getL}
    ),
    [](const ::testing::TestParamInfo<Inc8TestParameters>& info) { return info.param.name; }
);