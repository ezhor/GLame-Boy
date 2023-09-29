#include "pch.h"
#include "./TestUtils.h"

namespace EmulatorTests {
	TEST(ProgramCounter, CorrectInitialValue) {
		Emulator* emulator = TestUtils::GetEmulator();

		EXPECT_EQ(emulator->cpu.registers.getPC(), INITIAL_PROGRAM_COUNTER);

		delete emulator;
	}
}