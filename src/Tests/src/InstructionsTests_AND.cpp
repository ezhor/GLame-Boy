#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(AND_B, LogicAnd) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA0;
		u8 baseValue = 0b00111100;
		u8 mask = 0b11110000;
		u8 maskedValue = 0b00110000;

		emulator->cpu.registers.setA(baseValue);
		emulator->cpu.registers.setB(mask);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), maskedValue);

		delete emulator;
	}

	TEST(AND_C, LogicAnd) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA1;
		u8 baseValue = 0b00111100;
		u8 mask = 0b11110000;
		u8 maskedValue = 0b00110000;

		emulator->cpu.registers.setA(baseValue);
		emulator->cpu.registers.setC(mask);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), maskedValue);

		delete emulator;
	}

	TEST(AND_D, LogicAnd) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA2;
		u8 baseValue = 0b00111100;
		u8 mask = 0b11110000;
		u8 maskedValue = 0b00110000;

		emulator->cpu.registers.setA(baseValue);
		emulator->cpu.registers.setD(mask);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), maskedValue);

		delete emulator;
	}

	TEST(AND_E, LogicAnd) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA3;
		u8 baseValue = 0b00111100;
		u8 mask = 0b11110000;
		u8 maskedValue = 0b00110000;

		emulator->cpu.registers.setA(baseValue);
		emulator->cpu.registers.setE(mask);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), maskedValue);

		delete emulator;
	}

	TEST(AND_H, LogicAnd) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA4;
		u8 baseValue = 0b00111100;
		u8 mask = 0b11110000;
		u8 maskedValue = 0b00110000;

		emulator->cpu.registers.setA(baseValue);
		emulator->cpu.registers.setH(mask);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), maskedValue);

		delete emulator;
	}

	TEST(AND_L, LogicAnd) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA5;
		u8 baseValue = 0b00111100;
		u8 mask = 0b11110000;
		u8 maskedValue = 0b00110000;

		emulator->cpu.registers.setA(baseValue);
		emulator->cpu.registers.setL(mask);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), maskedValue);

		delete emulator;
	}

	TEST(AND_mem_HL, LogicAnd) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA6;
		u8 baseValue = 0b00111100;
		u8 mask = 0b11110000;
		u8 maskedValue = 0b00110000;
		u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setA(baseValue);
		emulator->cpu.registers.setHL(memoryLocation);
		emulator->cpu.bus->write(memoryLocation, mask);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), maskedValue);

		delete emulator;
	}

	TEST(AND_A, SameValue) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA7;
		u8 baseValue = 0b00111100;

		emulator->cpu.registers.setA(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), baseValue);

		delete emulator;
	}

	TEST(AND_A, ZeroFlagEnabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA7;
		u8 baseValue = 0;

		emulator->cpu.registers.setA(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(Z_FLAG), true);

		delete emulator;
	}

	TEST(AND_A, ZeroFlagDisabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA7;
		u8 baseValue = 0b00111100;

		emulator->cpu.registers.setA(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(Z_FLAG), false);

		delete emulator;
	}

	TEST(AND_A, SubtractFlagDisabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA7;
		u8 baseValue = 0b00111100;

		emulator->cpu.registers.setA(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(N_FLAG), false);

		delete emulator;
	}

	TEST(AND_A, HalfCarryFlagEnabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA7;
		u8 baseValue = 0b00111100;

		emulator->cpu.registers.setA(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(H_FLAG), true);

		delete emulator;
	}

	TEST(AND_A, CarryFlagDisabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 instruction = 0xA7;
		u8 baseValue = 0b00111100;

		emulator->cpu.registers.setA(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(C_FLAG), false);

		delete emulator;
	}
}