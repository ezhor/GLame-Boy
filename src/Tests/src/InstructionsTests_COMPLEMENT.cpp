#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(CPL, Complement) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0x2F;
		u8 initialValue = 0b01010101;
		u8 expectedValue = 0b10101010;

		emulator->cpu.registers.setA(initialValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), expectedValue);

		delete emulator;
	}

	TEST(CCF, ComplementEnableCarryFlag) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0x3F;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(C_FLAG), true);

		delete emulator;
	}

	TEST(CCF, ComplementDisableCarryFlag) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0x3F;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(C_FLAG), false);

		delete emulator;
	}

}