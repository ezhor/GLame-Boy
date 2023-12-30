#include "Cpu.h"
#include "Renderer.h"
#include "Ppu.h"

#pragma once
class Emulator
{
public:
	Emulator() :bus(), cpu(&bus), renderer(), ppu(&bus, &renderer) {
		instances++;
	}

	inline static int instances = 0;
	Bus bus;
	Cpu cpu;
	Renderer renderer;
	Ppu ppu;

	void init();
	void run(bool multithread, bool testMode);
};
