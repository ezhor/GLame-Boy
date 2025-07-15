#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(POP_BC, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xC1;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(POP_BC, Value) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xC1;
		u16 initialStackPointer = 0xFFFC;
		u16 value = 0x1234;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getBC(), value);

		delete emulator;
	}

	TEST(POP_DE, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xD1;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(POP_DE, Value) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xD1;
		u16 initialStackPointer = 0xFFFC;
		u16 value = 0x1234;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getDE(), value);

		delete emulator;
	}

	TEST(POP_HL, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xE1;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(POP_HL, Value) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xE1;
		u16 initialStackPointer = 0xFFFC;
		u16 value = 0x1234;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getHL(), value);

		delete emulator;
	}

	TEST(POP_AF, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xF1;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(POP_AF, Value) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 popInstruction = 0xF1;
		u16 initialStackPointer = 0xFFFC;
		u16 value = 0x1234;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, popInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getAF(), value);

		delete emulator;
	}
}