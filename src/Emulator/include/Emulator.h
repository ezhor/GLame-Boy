#pragma once
#include "Cpu.h"
#include "Renderer.h"
#include "Ppu.h"

#pragma once
class Emulator
{
public:
	explicit Emulator() : cpu(&bus), ppu(&bus, &renderer) {
		instances++;
	}

	inline static int instances = 0;
	Bus bus;
	Cpu cpu;
	Renderer renderer;
	Ppu ppu;

	void init(const char* romPath);
	void run(bool multithread, bool testMode);
};
