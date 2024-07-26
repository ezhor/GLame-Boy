#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(JP_a16, Jump) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 jumpInstruction = 0xC3;
		u16 targetLocation = 0x150;

		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER, jumpInstruction);
		emulator->cpu.bus->write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetLocation);

		delete emulator;
	}

	TEST(LD_A_d8, LoadValueToRegister) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 loadInstruction = 0x3E;
		u8 targetValue = 0x27;

		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER, loadInstruction);
		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER + 1, targetValue);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), targetValue);

		delete emulator;
	}

	TEST(LD_mem_a16_A, LoadValueToMemory) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 intruction = 0xEA;
		u16 memoryLocation = 0x153;
		u8 memoryValue = 0x27;

		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER, intruction);
		emulator->cpu.bus->write16(INITIAL_PROGRAM_COUNTER + 1, memoryLocation);
		emulator->cpu.registers.setA(memoryValue);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), memoryValue);

		delete emulator;
	}

	TEST(LD_A_mem_a16, LoadValueToRegister) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 intruction = 0xFA;
		u16 memoryLocation = 0x153;
		u8 memoryValue = 0x27;

		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER, intruction);
		emulator->cpu.bus->write16(INITIAL_PROGRAM_COUNTER + 1, memoryLocation);
		emulator->cpu.bus->write(memoryLocation, memoryValue);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), memoryValue);

		delete emulator;
	}

	TEST(CP_d8, ZeroFlagTrueWhenEquals) {
		TestUtils::testCP(0x01, 0x01, Z_FLAG, true);
	}

	TEST(CP_d8, ZeroFlagFalseWhenNotEquals) {
		TestUtils::testCP(0x01, 0x02, Z_FLAG, false);
	}

	TEST(CP_d8, SubtractionFlagTrueWhenEquals) {
		TestUtils::testCP(0x01, 0x01, N_FLAG, true);
	}

	TEST(CP_d8, SubtractionFlagTrueWhenNotEquals) {
		TestUtils::testCP(0x01, 0x02, N_FLAG, true);
	}

	TEST(CP_d8, CarryFlagTrueWhenGreater) {
		TestUtils::testCP(0x01, 0x02, C_FLAG, true);
	}

	TEST(CP_d8, CarryFlagTrueWhenEquals) {
		TestUtils::testCP(0x01, 0x02, C_FLAG, true);
	}

	TEST(CP_d8, CarryFlagFalseWhenLess) {
		TestUtils::testCP(0x02, 0x01, C_FLAG, false);
	}

	TEST(CP_d8, HalfCarryFlagTrueWhenGreater) {
		TestUtils::testCP(0x01, 0x02, H_FLAG, true);
	}

	TEST(CP_d8, HalfCarryFlagTrueWhenEquals) {
		TestUtils::testCP(0x01, 0x02, H_FLAG, true);
	}

	TEST(CP_d8, HalfCarryFlagFalseWhenLess) {
		TestUtils::testCP(0x02, 0x01, H_FLAG, false);
	}

	TEST(JR_NZ_r8, Jump) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 jumpInstruction = 0x20;
		u8 offset = 0xFC;
		u16 startingLocation = 0x216;
		u16 targetLocation = 0x214;

		emulator->cpu.registers.setPC(startingLocation);
		emulator->cpu.bus->write(startingLocation, jumpInstruction);
		emulator->cpu.bus->write(startingLocation + 1, offset);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetLocation);

		delete emulator;
	}

	TEST(JR_NZ_r8, NoJump) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 jumpInstruction = 0x20;
		u8 offset = 0xFC;
		u16 startingLocation = 0x216;
		u16 noJumpTargetLocation = 0x218;

		emulator->cpu.registers.setFlag(Z_FLAG, true);
		emulator->cpu.registers.setPC(startingLocation);
		emulator->cpu.bus->write(startingLocation, jumpInstruction);
		emulator->cpu.bus->write(startingLocation + 1, offset);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), noJumpTargetLocation);

		delete emulator;
	}

	TEST(LDH_mem_a8_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 loadInstruction = 0xE0;
		u8 immediateDataLocation = 0x27;
		u16 targetLocation = 0xFF00 + immediateDataLocation;
		u16 value = 0x28;

		emulator->cpu.registers.setA(value);
		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER, loadInstruction);
		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER + 1, immediateDataLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(targetLocation), value);

		delete emulator;
	}
}