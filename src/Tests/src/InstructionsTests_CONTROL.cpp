#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(NOP, DoNothing) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0x00;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		delete emulator;
	}

	TEST(DI, DisableInterrupts) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xF3;

		emulator->cpu.setInterrupts(true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.interruptsEnabled(), false);

		delete emulator;
	}

	TEST(EI, EnableInterrupts) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xFB;

		emulator->cpu.setInterrupts(false);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.interruptsEnabled(), true);

		delete emulator;
	}

}