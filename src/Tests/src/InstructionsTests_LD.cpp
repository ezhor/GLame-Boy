#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(LD_BC_d16, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x01;
		constexpr u16 value = 0x1234;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getBC(), value);

		delete emulator;
	}

	TEST(LD_DE_d16, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x11;
		constexpr u16 value = 0x1234;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getDE(), value);

		delete emulator;
	}

	TEST(LD_HL_d16, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x21;
		constexpr u16 value = 0x1234;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getHL(), value);

		delete emulator;
	}

	TEST(LD_SP_d16, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x31;
		constexpr u16 value = 0x1234;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), value);

		delete emulator;
	}

	TEST(LD_mem_BC_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x02;
		constexpr u16 memoryLocation = 0x1234;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setBC(memoryLocation);
		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_DE_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x12;
		constexpr u16 memoryLocation = 0x1234;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setDE(memoryLocation);
		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_HL_inc_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x22;
		constexpr u16 memoryLocation = 0x1234;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_HL_inc_A, RegisterIncrement) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x22;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getHL(), memoryLocation + 1);

		delete emulator;
	}

	TEST(LD_mem_HL_dec_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x32;
		constexpr u16 memoryLocation = 0x1234;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_HL_dec_A, RegisterDecrement) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x32;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getHL(), memoryLocation - 1);

		delete emulator;
	}

	TEST(LD_B_d8, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x06;
		constexpr u8 value = 0x27;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), value);

		delete emulator;
	}

	TEST(LD_D_d8, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x16;
		constexpr u8 value = 0x27;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), value);

		delete emulator;
	}

	TEST(LD_H_d8, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x26;
		constexpr u8 value = 0x27;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), value);

		delete emulator;
	}

	TEST(LD_mem_HL_d8, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x36;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_a16_SP, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x08;
		constexpr u16 value = 0x5678;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setSP(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, memoryLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read16(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_A_mem_BC, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x0A;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setBC(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_mem_DE, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x1A;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setDE(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_mem_HL_inc, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x2A;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_mem_HL_inc, RegisterIncrement) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x2A;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getHL(), memoryLocation + 1);

		delete emulator;
	}

	TEST(LD_A_mem_HL_dec, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x3A;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_mem_HL_dec, RegisterDecrement) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x3A;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getHL(), memoryLocation - 1);

		delete emulator;
	}

	TEST(LD_C_d8, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x0E;
		constexpr u8 value = 0x27;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), value);

		delete emulator;
	}

	TEST(LD_E_d8, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x1E;
		constexpr u8 value = 0x27;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), value);

		delete emulator;
	}

	TEST(LD_L_d8, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x2E;
		constexpr u8 value = 0x27;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), value);

		delete emulator;
	}

	TEST(LD_A_d8, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x3E;
		constexpr u8 value = 0x27;

		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, value);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_B_B, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x40;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setB(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), value);

		delete emulator;
	}

	TEST(LD_B_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x41;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), value);

		delete emulator;
	}

	TEST(LD_B_D, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x42;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setD(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), value);

		delete emulator;
	}

	TEST(LD_B_E, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x43;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setE(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), value);

		delete emulator;
	}

	TEST(LD_B_H, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x44;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setH(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), value);

		delete emulator;
	}

	TEST(LD_B_L, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x45;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setL(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), value);

		delete emulator;
	}

	TEST(LD_B_mem_hl, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x46;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), value);

		delete emulator;
	}

	TEST(LD_B_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x47;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getB(), value);

		delete emulator;
	}

	TEST(LD_C_B, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x48;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setB(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), value);

		delete emulator;
	}

	TEST(LD_C_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x49;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), value);

		delete emulator;
	}

	TEST(LD_C_D, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x4A;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setD(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), value);

		delete emulator;
	}

	TEST(LD_C_E, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x4B;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setE(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), value);

		delete emulator;
	}

	TEST(LD_C_H, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x4C;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setH(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), value);

		delete emulator;
	}

	TEST(LD_C_L, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x4D;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setL(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), value);

		delete emulator;
	}

	TEST(LD_C_mem_hl, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x4E;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), value);

		delete emulator;
	}

	TEST(LD_C_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x4F;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getC(), value);

		delete emulator;
	}

	TEST(LD_D_B, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x50;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setB(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), value);

		delete emulator;
	}

	TEST(LD_D_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x51;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), value);

		delete emulator;
	}

	TEST(LD_D_D, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x52;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setD(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), value);

		delete emulator;
	}

	TEST(LD_D_E, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x53;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setE(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), value);

		delete emulator;
	}

	TEST(LD_D_H, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x54;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setH(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), value);

		delete emulator;
	}

	TEST(LD_D_L, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x55;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setL(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), value);

		delete emulator;
	}

	TEST(LD_D_mem_hl, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x56;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), value);

		delete emulator;
	}

	TEST(LD_D_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x57;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getD(), value);

		delete emulator;
	}

	TEST(LD_E_B, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x58;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setB(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), value);

		delete emulator;
	}

	TEST(LD_E_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x59;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), value);

		delete emulator;
	}

	TEST(LD_E_D, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x5A;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setD(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), value);

		delete emulator;
	}

	TEST(LD_E_E, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x5B;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setE(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), value);

		delete emulator;
	}

	TEST(LD_E_H, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x5C;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setH(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), value);

		delete emulator;
	}

	TEST(LD_E_L, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x5D;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setL(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), value);

		delete emulator;
	}

	TEST(LD_E_mem_hl, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x5E;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), value);

		delete emulator;
	}

	TEST(LD_E_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x5F;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getE(), value);

		delete emulator;
	}

	TEST(LD_H_B, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x60;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setB(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), value);

		delete emulator;
	}

	TEST(LD_H_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x61;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), value);

		delete emulator;
	}

	TEST(LD_H_D, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x62;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setD(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), value);

		delete emulator;
	}

	TEST(LD_H_E, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x63;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setE(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), value);

		delete emulator;
	}

	TEST(LD_H_H, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x64;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setH(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), value);

		delete emulator;
	}

	TEST(LD_H_L, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x65;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setL(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), value);

		delete emulator;
	}

	TEST(LD_H_mem_hl, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x66;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), value);

		delete emulator;
	}

	TEST(LD_H_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x67;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getH(), value);

		delete emulator;
	}

	TEST(LD_L_B, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x68;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setB(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), value);

		delete emulator;
	}

	TEST(LD_L_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x69;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), value);

		delete emulator;
	}

	TEST(LD_L_D, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x6A;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setD(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), value);

		delete emulator;
	}

	TEST(LD_L_E, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x6B;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setE(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), value);

		delete emulator;
	}

	TEST(LD_L_H, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x6C;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setH(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), value);

		delete emulator;
	}

	TEST(LD_L_L, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x6D;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setL(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), value);

		delete emulator;
	}

	TEST(LD_L_mem_hl, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x6E;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), value);

		delete emulator;
	}

	TEST(LD_L_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x6F;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getL(), value);

		delete emulator;
	}

	TEST(LD_mem_HL_B, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x70;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setB(value);
		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_HL_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x71;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setC(value);
		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_HL_D, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x72;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setD(value);
		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_HL_E, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x73;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setE(value);
		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_HL_H, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x74;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), emulator->cpu.registers.getH());

		delete emulator;
	}

	TEST(LD_mem_HL_L, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x75;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), emulator->cpu.registers.getL());

		delete emulator;
	}

	TEST(LD_mem_HL_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x77;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setA(value);
		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_A_B, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x78;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setB(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x79;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_D, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x7A;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setD(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_E, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x7B;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setE(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_H, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x7C;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setH(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_L, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x7D;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setL(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_mem_hl, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x7E;
		constexpr u8 value = 0x27;
		constexpr u16 memoryLocation = 0x1234;

		emulator->cpu.registers.setHL(memoryLocation);
		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_A_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0x7F;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_mem_a8_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0xE0;
		constexpr u8 value = 0x27;
		constexpr u16 memoryOffset = 0x48;
		constexpr u16 memoryLocation = HRAM_LOCAITON_START + memoryOffset;

		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, memoryOffset);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_A_a8, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0xF0;
		constexpr u8 value = 0x27;
		constexpr u16 memoryOffset = 0x48;
		constexpr u16 memoryLocation = HRAM_LOCAITON_START + memoryOffset;

		emulator->bus.write(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1, memoryOffset);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}

	TEST(LD_mem_C_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0xE2;
		constexpr u8 value = 0x27;
		constexpr u16 memoryOffset = 0x48;
		constexpr u16 memoryLocation = HRAM_LOCAITON_START + memoryOffset;

		emulator->cpu.registers.setA(value);
		emulator->cpu.registers.setC(memoryOffset);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_mem_A_C, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0xF2;
		constexpr u8 value = 0x27;
		constexpr u16 memoryOffset = 0x48;
		constexpr u16 memoryLocation = HRAM_LOCAITON_START + memoryOffset;

		emulator->cpu.registers.setA(memoryOffset);
		emulator->cpu.registers.setC(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_HL_SP_plus_r8, LoadAdditive) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0xF8;
		constexpr u16 baseValue = 0x1234;
		constexpr u8 offsetValue = 0x10;
		constexpr u16 targetValue = 0x1244;

		emulator->cpu.registers.setSP(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1 , offsetValue);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getHL(), targetValue);

		delete emulator;
	}

	TEST(LD_HL_SP_plus_r8, LoadSubstractive) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0xF8;
		constexpr u16 baseValue = 0x1234;
		constexpr u8 offsetValue = 0xF0;
		constexpr u16 targetValue = 0x1224;

		emulator->cpu.registers.setSP(baseValue);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER + 1 , offsetValue);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getHL(), targetValue);

		delete emulator;
	}

	TEST(LD_SP_HL, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0xF9;
		constexpr u16 value = 0x1234;

		emulator->cpu.registers.setHL(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getSP(), value);

		delete emulator;
	}

	TEST(LD_mem_a16_A, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0xEA;
		constexpr u16 memoryLocation = 0x1234;
		constexpr u8 value = 0x27;

		emulator->cpu.registers.setA(value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, memoryLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->bus.read(memoryLocation), value);

		delete emulator;
	}

	TEST(LD_A_mem_a16, Load) {
		Emulator* emulator = TestUtils::getEmulator();
		constexpr u8 instruction = 0xFA;
		constexpr u16 memoryLocation = 0x1234;
		constexpr u8 value = 0x27;

		emulator->bus.write16(memoryLocation, value);
		emulator->bus.write(INITIAL_PROGRAM_COUNTER, instruction);
		emulator->bus.write16(INITIAL_PROGRAM_COUNTER + 1, memoryLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), value);

		delete emulator;
	}
}