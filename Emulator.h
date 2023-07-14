#include "Cpu.h"
#include "Renderer.h"
#include "Ppu.h"

#pragma once
class Emulator
{
public:
	Emulator() :bus(), cpu(&bus), renderer(), ppu(&bus, &renderer) {
		cpu.loadInstructions();
		renderer.init();
		ppu.init();
	}
	void run(bool multithread, bool testMode);

private:
	Bus bus;
	Cpu cpu;
	Renderer renderer;
	Ppu ppu;
};

