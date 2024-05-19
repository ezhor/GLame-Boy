#include "TestUtils.h"
#include <gtest/gtest.h>

Emulator* TestUtils::getEmulator()
{
	Emulator* emulator = new Emulator();
	emulator->bus.load(nullptr);
	emulator->cpu.verbose = false;
	emulator->cpu.loadInstructions();
	return emulator;
}

void TestUtils::testCP(u8 registerValue, u8 immediateValue, u8 flag, bool flagValue){
	Emulator* emulator = TestUtils::getEmulator();
	u8 intruction = 0xFE;

	emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER, intruction);
	emulator->cpu.bus->write(INITIAL_PROGRAM_COUNTER + 1, immediateValue);
	emulator->cpu.registers.setA(registerValue);
	emulator->cpu.tick();

	EXPECT_EQ(emulator->cpu.registers.getFlag(flag), flagValue);

	delete emulator;
}
