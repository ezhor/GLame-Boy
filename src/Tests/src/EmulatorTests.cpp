#include <gtest/gtest.h>
#include "./TestUtils.h"

namespace EmulatorTests {

	TEST(MemoryInstances, SingleBusInstance) {
		Bus::instances = 0;
		Emulator* emulator = TestUtils::getEmulator();

		EXPECT_EQ(Bus::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SingleCpuInstance) {
		Cpu::instances = 0;
		Emulator* emulator = TestUtils::getEmulator();

		EXPECT_EQ(Cpu::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SingleEmulatorInstance) {
		Emulator::instances = 0;
		Emulator* emulator = TestUtils::getEmulator();

		EXPECT_EQ(Emulator::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SinglePpuInstance) {
		Ppu::instances = 0;
		Emulator* emulator = TestUtils::getEmulator();

		EXPECT_EQ(Ppu::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SingleRegistersInstance) {
		Registers::instances = 0;
		Emulator* emulator = TestUtils::getEmulator();

		EXPECT_EQ(Registers::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SingleRendererInstance) {
		Renderer::instances = 0;
		Emulator* emulator = TestUtils::getEmulator();

		EXPECT_EQ(Renderer::instances, 1);

		delete emulator;
	}

	TEST(InitialValue, ProgramCounter) {
		Emulator* emulator = TestUtils::getEmulator();

		EXPECT_EQ(emulator->cpu.registers.getPC(), INITIAL_PROGRAM_COUNTER);

		delete emulator;
	}

	TEST(InitialValue, StackPointer) {
		Emulator* emulator = TestUtils::getEmulator();

		EXPECT_EQ(emulator->cpu.registers.getSP(), INITIAL_STACK_POINTER);

		delete emulator;
	}
}