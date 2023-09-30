#include "pch.h"
#include "./TestUtils.h"

namespace EmulatorTests {

	TEST(MemoryInstances, SingleBusInstance) {
		Bus::instances = 0;
		Emulator* emulator = TestUtils::GetEmulator();

		EXPECT_EQ(Bus::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SingleCpuInstance) {
		Cpu::instances = 0;
		Emulator* emulator = TestUtils::GetEmulator();

		EXPECT_EQ(Cpu::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SingleEmulatorInstance) {
		Emulator::instances = 0;
		Emulator* emulator = TestUtils::GetEmulator();

		EXPECT_EQ(Emulator::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SinglePpuInstance) {
		Ppu::instances = 0;
		Emulator* emulator = TestUtils::GetEmulator();

		EXPECT_EQ(Ppu::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SingleRegistersInstance) {
		Registers::instances = 0;
		Emulator* emulator = TestUtils::GetEmulator();

		EXPECT_EQ(Registers::instances, 1);

		delete emulator;
	}

	TEST(MemoryInstances, SingleRendererInstance) {
		Renderer::instances = 0;
		Emulator* emulator = TestUtils::GetEmulator();

		EXPECT_EQ(Renderer::instances, 1);

		delete emulator;
	}

	TEST(ProgramCounter, CorrectInitialValue) {
		Emulator* emulator = TestUtils::GetEmulator();

		EXPECT_EQ(emulator->cpu.registers.getPC(), INITIAL_PROGRAM_COUNTER);

		delete emulator;
	}
}