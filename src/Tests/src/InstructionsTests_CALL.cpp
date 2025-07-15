#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(CALL_NZ_a16, Jump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC4;
		u16 targetStackPointer = 0xFFFC;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_NZ_a16, Jump_Stack) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC4;
		u16 stackLocation = 0xFFFC;
		u16 targetStackPointer = INITIAL_PROGRAM_COUNTER + 3;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(stackLocation), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_NZ_a16, Jump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC4;
		u16 targetLocation = 0x1234;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetLocation);

		delete emulator;
	}

	TEST(CALL_NZ_a16, NoJump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC4;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_NZ_a16, NoJump_Stack) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC4;
		u16 stackLocation = 0xFFFC;
		u16 targetStackPointer = 0x0000;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(stackLocation), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_NZ_a16, NoJump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xC4;
		u16 targetLocation = 0x1234;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), INITIAL_PROGRAM_COUNTER + 3);

		delete emulator;
	}

	TEST(CALL_Z_a16, Jump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xCC;
		u16 targetStackPointer = 0xFFFC;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_Z_a16, Jump_Stack) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xCC;
		u16 stackLocation = 0xFFFC;
		u16 targetStackPointer = INITIAL_PROGRAM_COUNTER + 3;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(stackLocation), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_Z_a16, Jump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xCC;
		u16 targetLocation = 0x1234;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetLocation);

		delete emulator;
	}

	TEST(CALL_Z_a16, NoJump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xCC;
		u16 targetStackPointer = 0xFFFE;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_Z_a16, NoJump_Stack) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xCC;
		u16 stackLocation = 0xFFFC;
		u16 targetStackPointer = 0x0000;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(stackLocation), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_Z_a16, NoJump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xCC;
		u16 targetLocation = 0x1234;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), INITIAL_PROGRAM_COUNTER + 3);

		delete emulator;
	}

	TEST(CALL_a16, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xCD;
		u16 targetStackPointer = 0xFFFC;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_a16, Stack) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xCD;
		u16 stackLocation = 0xFFFC;
		u16 targetStackPointer = INITIAL_PROGRAM_COUNTER + 3;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(stackLocation), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_a16, ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xCD;
		u16 targetLocation = 0x1234;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetLocation);

		delete emulator;
	}

	TEST(CALL_NC_a16, Jump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD4;
		u16 targetStackPointer = 0xFFFC;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_NC_a16, Jump_Stack) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD4;
		u16 stackLocation = 0xFFFC;
		u16 targetStackPointer = INITIAL_PROGRAM_COUNTER + 3;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(stackLocation), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_NC_a16, Jump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD4;
		u16 targetLocation = 0x1234;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetLocation);

		delete emulator;
	}

	TEST(CALL_NC_a16, NoJump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD4;
		u16 targetStackPointer = 0xFFFE;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_NC_a16, NoJump_Stack) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD4;
		u16 stackLocation = 0xFFFC;
		u16 targetStackPointer = 0x0000;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(stackLocation), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_NC_a16, NoJump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xD4;
		u16 targetLocation = 0x1234;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), INITIAL_PROGRAM_COUNTER + 3);

		delete emulator;
	}

	TEST(CALL_C_a16, Jump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xDC;
		u16 targetStackPointer = 0xFFFC;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_C_a16, Jump_Stack) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xDC;
		u16 stackLocation = 0xFFFC;
		u16 targetStackPointer = INITIAL_PROGRAM_COUNTER + 3;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(stackLocation), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_C_a16, Jump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xDC;
		u16 targetLocation = 0x1234;

		emulator->cpu.registers.setFlag(C_FLAG, true);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetLocation);

		delete emulator;
	}

	TEST(CALL_C_a16, NoJump_StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xDC;
		u16 targetStackPointer = 0xFFFE;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_C_a16, NoJump_Stack) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xDC;
		u16 stackLocation = 0xFFFC;
		u16 targetStackPointer = 0x0000;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(stackLocation), targetStackPointer);

		delete emulator;
	}

	TEST(CALL_C_a16, NoJump_ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xDC;
		u16 targetLocation = 0x1234;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), INITIAL_PROGRAM_COUNTER + 3);

		delete emulator;
	}

}