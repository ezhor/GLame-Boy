#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace InstructionsTests {

	TEST(JP_a16, Jump) {
		Emulator* emulator = TestUtils::GetEmulator();
		emulator->bus.load(nullptr);
		emulator->cpu.loadInstructions();
		u8 jumpInstruction = 0xC3;
		u16 targetLocation = 0x150;

		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER, jumpInstruction);
		emulator->cpu.bus->write16(INITIAL_PROGRAM_COUNTER + 1, targetLocation);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getPC(), targetLocation);

		delete emulator;
	}

	TEST(LD_A_d8, LoadValueToRegister) {
		Emulator* emulator = TestUtils::GetEmulator();
		emulator->bus.load(nullptr);
		emulator->cpu.loadInstructions();
		u8 loadInstruction = 0x3E;
		u8 targetValue = 0x27;

		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER, loadInstruction);
		emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER + 1, targetValue);
		emulator->cpu.tick();

		EXPECT_EQ(emulator->cpu.registers.getA(), targetValue);

		delete emulator;
	}

	TEST(LD_mem_a16_A, LoadValueToMemory) {
		Emulator* emulator = TestUtils::GetEmulator();
		emulator->bus.load(nullptr);
		emulator->cpu.loadInstructions();
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
		Emulator* emulator = TestUtils::GetEmulator();
		emulator->bus.load(nullptr);
		emulator->cpu.loadInstructions();
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
}