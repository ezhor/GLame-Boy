#include "pch.h"
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(JPa16, Jump) {
		Emulator* emulator = TestUtils::GetEmulator();
		emulator->bus.load(nullptr);
		emulator->cpu.loadInstructions();
		u8 jumpInstruction = 0xC3;
		u16 jumpTarget = 0x27;

		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER, jumpInstruction);
		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER + 1, 0x50);
		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER + 2, 0x01);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), 0x150);

		delete emulator;
	}

}