#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(RET_NZ, Jump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC0;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(RET_NZ, Jump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC0;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = 0x1234;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RET_NZ, NoJump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC0;
		u16 initialStackPointer = 0xFFFC;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), initialStackPointer);

		delete emulator;
	}

	TEST(RET_NZ, NoJump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC0;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = INITIAL_PROGRAM_COUNTER + 1;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RET_Z, Jump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC8;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(RET_Z, Jump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC8;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = 0x1234;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RET_Z, NoJump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC8;
		u16 initialStackPointer = 0xFFFC;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), initialStackPointer);

		delete emulator;
	}

	TEST(RET_Z, NoJump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC8;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = INITIAL_PROGRAM_COUNTER + 1;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RET, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC9;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(RET, ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC9;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = 0x1234;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RET_NC, Jump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD0;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(RET_NC, Jump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD0;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = 0x1234;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RET_NC, NoJump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD0;
		u16 initialStackPointer = 0xFFFC;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), initialStackPointer);

		delete emulator;
	}

	TEST(RET_NC, NoJump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD0;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = INITIAL_PROGRAM_COUNTER + 1;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RET_C, Jump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD8;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(RET_C, Jump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD8;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = 0x1234;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RET_C, NoJump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD8;
		u16 initialStackPointer = 0xFFFC;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), initialStackPointer);

		delete emulator;
	}

	TEST(RET_C, NoJump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD8;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = INITIAL_PROGRAM_COUNTER + 1;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RETI, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD9;
		u16 initialStackPointer = 0xFFFC;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(RETI, ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD9;
		u16 initialStackPointer = 0xFFFC;
		u16 targetProgramCounter = 0x1234;

		emulator->cpu.registers.setSP(initialStackPointer);
		emulator->bus.write16(initialStackPointer, targetProgramCounter);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetProgramCounter);

		delete emulator;
	}

	TEST(RETI, EnableInterruptions) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD9;

		emulator->cpu.setInterrupts(false);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.interruptsEnabled(), true);

		delete emulator;
	}

}