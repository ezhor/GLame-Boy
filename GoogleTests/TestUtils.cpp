#include "pch.h"
#include "TestUtils.h"

Emulator* TestUtils::GetEmulator()
{
	Emulator* emulator = new Emulator();
	emulator->bus.load(nullptr);
	emulator->cpu.loadInstructions();
	return emulator;
}
