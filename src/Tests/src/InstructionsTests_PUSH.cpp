#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(PUSH_BC, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xC5;
		u16 targetStackPointer = 0xFFFC;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(PUSH_BC, Value) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xC5;
		u16 memoryLocation = 0xFFFC;
		u16 value = 0x1234;


		emulator->cpu.registers.setBC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(memoryLocation), value);

		delete emulator;
	}

	TEST(PUSH_DE, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xD5;
		u16 targetStackPointer = 0xFFFC;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(PUSH_DE, Value) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xD5;
		u16 memoryLocation = 0xFFFC;
		u16 value = 0x1234;


		emulator->cpu.registers.setDE(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(memoryLocation), value);

		delete emulator;
	}

	TEST(PUSH_HL, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xE5;
		u16 targetStackPointer = 0xFFFC;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(PUSH_HL, Value) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xE5;
		u16 memoryLocation = 0xFFFC;
		u16 value = 0x1234;


		emulator->cpu.registers.setHL(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(memoryLocation), value);

		delete emulator;
	}

	TEST(PUSH_AF, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xF5;
		u16 targetStackPointer = 0xFFFC;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(PUSH_AF, Value) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xF5;
		u16 memoryLocation = 0xFFFC;
		u16 value = 0x1234;


		emulator->cpu.registers.setAF(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(memoryLocation), value);

		delete emulator;
	}
}