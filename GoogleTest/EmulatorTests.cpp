#include "pch.h"
#include "../Emulator.h"

namespace EmulatorTests{
	Emulator GetEmulator() {
		Emulator emulator = Emulator();
		emulator.bus.load(nullptr);
		emulator.cpu.loadInstructions();
		return emulator;
	}

	TEST(Cpu, InitialProgramCounter) {
		Emulator emulator = GetEmulator();
		EXPECT_EQ(emulator.cpu.registers.getPC(), INITIAL_PROGRAM_COUNTER);
	}

	TEST(Cpu, JP_a16__jump) {
		Emulator emulator = GetEmulator();
		u8 jumpInstruction = 0xC3;
		u16 jumpTarget = 0x27;

		emulator.bus.write(INITIAL_PROGRAM_COUNTER, jumpInstruction);
		emulator.bus.write(INITIAL_PROGRAM_COUNTER + 1, jumpTarget);
		emulator.cpu.tick();

		EXPECT_EQ(emulator.cpu.registers.getPC(), jumpTarget);
	}
}