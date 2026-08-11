#include <TestUtils.h>
#include <gtest/gtest.h>
#include "Emulator.h"

struct JrTestParameters {
    std::string name;
    u8 instruction;
    s8 jump;
    u16 initialPosition;
    u16 expectedPosition;
    u8 flags;
};

class JrTest : public ::testing::TestWithParam<JrTestParameters> {
protected:
    Emulator* emulator = TestUtils::getEmulator();

    void TearDown() override {
        delete emulator;
    }
};

TEST_P(JrTest, Jump) {
    const auto& param = GetParam();
    emulator->cpu.registers.setF(param.flags);
    emulator->cpu.registers.setPC(param.initialPosition);

    emulator->bus.write(param.initialPosition, param.instruction);
    emulator->bus.write(param.initialPosition + 1, param.jump);
    emulator->cpu.tick();

    EXPECT_EQ(emulator->cpu.registers.getPC(), param.expectedPosition);
}

INSTANTIATE_TEST_SUITE_P(
    JR,
    JrTest,
    ::testing::Values(
        JrTestParameters{"JR_r8_Jump", 0x18, 10, 500, 512, NO_FLAG},
        JrTestParameters{"JR_Z_r8_Jump", 0x28, 10, 500, 512, Z_FLAG},
        JrTestParameters{"JR_C_r8_Jump", 0x38, 10, 500, 512, C_FLAG},
        JrTestParameters{"JR_NZ_r8_Jump", 0x20, 10, 500, 512, NO_FLAG},
        JrTestParameters{"JR_NC_r8_Jump", 0x30, 10, 500, 512, NO_FLAG},

        JrTestParameters{"JR_r8_ReverseJump", 0x18, -10, 500, 492, NO_FLAG},
        JrTestParameters{"JR_Z_r8_ReverseJump", 0x28, -10, 500, 492, Z_FLAG},
        JrTestParameters{"JR_C_r8_ReverseJump", 0x38, -10, 500, 492, C_FLAG},
        JrTestParameters{"JR_NZ_r8_ReverseJump", 0x20, -10, 500, 492, NO_FLAG},
        JrTestParameters{"JR_NC_r8_ReverseJump", 0x30, -10, 500, 492, NO_FLAG},

        JrTestParameters{"JR_Z_r8_NoJump", 0x28, 10, 500, 502, NO_FLAG},
        JrTestParameters{"JR_C_r8_NoJump", 0x38, 10, 500, 502, NO_FLAG},
        JrTestParameters{"JR_NZ_r8_NoJump", 0x20, 10, 500, 502, Z_FLAG},
        JrTestParameters{"JR_NC_r8_NoJump", 0x30, 10, 500, 502, C_FLAG}
    ),
    [](const ::testing::TestParamInfo<JrTestParameters>& info) { return info.param.name; }
);