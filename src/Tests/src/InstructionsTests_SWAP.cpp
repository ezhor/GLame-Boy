#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(SWAP_B, Swap) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x30;
		u8 baseValue = 0b01011010;
		u8 swappedValue = 0b10100101;

		emulator->cpu.registers.setB(0b01011010);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), swappedValue);

		delete emulator;
	}

	TEST(SWAP_B, ZeroFlagEnabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x30;
		u8 baseValue = 0;

		emulator->cpu.registers.setB(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(Z_FLAG), true);

		delete emulator;
	}

	TEST(SWAP_B, ZeroFlagDisabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x30;
		u8 baseValue = 0b00111100;

		emulator->cpu.registers.setB(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(Z_FLAG), false);

		delete emulator;
	}

	TEST(SWAP_B, SubtractFlagDisabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x30;
		u8 baseValue = 0b00111100;

		emulator->cpu.registers.setB(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(N_FLAG), false);

		delete emulator;
	}

	TEST(SWAP_B, HalfCarryFlagDisabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x30;
		u8 baseValue = 0b00111100;

		emulator->cpu.registers.setB(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(H_FLAG), false);

		delete emulator;
	}

	TEST(SWAP_B, CarryFlagDisabled) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x30;
		u8 baseValue = 0b00111100;

		emulator->cpu.registers.setB(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getFlag(C_FLAG), false);

		delete emulator;
	}

	TEST(SWAP_C, Swap) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x31;
		u8 baseValue = 0b01011010;
		u8 swappedValue = 0b10100101;

		emulator->cpu.registers.setC(0b01011010);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), swappedValue);

		delete emulator;
	}

	TEST(SWAP_D, Swap) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x32;
		u8 baseValue = 0b01011010;
		u8 swappedValue = 0b10100101;

		emulator->cpu.registers.setD(0b01011010);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), swappedValue);

		delete emulator;
	}

	TEST(SWAP_E, Swap) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x33;
		u8 baseValue = 0b01011010;
		u8 swappedValue = 0b10100101;

		emulator->cpu.registers.setE(0b01011010);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), swappedValue);

		delete emulator;
	}

	TEST(SWAP_H, Swap) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x34;
		u8 baseValue = 0b01011010;
		u8 swappedValue = 0b10100101;

		emulator->cpu.registers.setH(0b01011010);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), swappedValue);

		delete emulator;
	}

	TEST(SWAP_L, Swap) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x35;
		u8 baseValue = 0b01011010;
		u8 swappedValue = 0b10100101;

		emulator->cpu.registers.setL(0b01011010);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), swappedValue);

		delete emulator;
	}

	TEST(SWAP_mem_HL, Swap) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x36;
		u8 baseValue = 0b01011010;
		u8 swappedValue = 0b10100101;
		u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), swappedValue);

		delete emulator;
	}

	TEST(SWAP_A, Swap) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 cbPrefix = 0xCB;
		u8 instruction = 0x37;
		u8 baseValue = 0b01011010;
		u8 swappedValue = 0b10100101;

		emulator->cpu.registers.setA(0b01011010);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, cbPrefix);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, instruction);
		emulator->cpu.tick();
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), swappedValue);

		delete emulator;
	}
}