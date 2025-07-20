#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(JP_a16, Jump) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 jumpInstruction = 0xC3;
		u16 targetLocation = 0x150;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, jumpInstruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetLocation);

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
		emulator->bus.write(startingLocation, jumpInstruction);
		emulator->bus.write(startingLocation + 1, offset);
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
		emulator->bus.write(startingLocation, jumpInstruction);
		emulator->bus.write(startingLocation + 1, offset);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), noJumpTargetLocation);

		delete emulator;
	}

	TEST(INC_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		u8 incrementInstruction = 0x0C;
		u8 value = 0x27;
		u8 targetValue = 0x28;

		emulator->cpu.registers.setC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, incrementInstruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), targetValue);

		delete emulator;
	}
}