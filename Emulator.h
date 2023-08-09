#include "Cpu.h"
#include "Renderer.h"
#include "Ppu.h"

#pragma once
class Emulator
{
public:
	Emulator() :bus(), cpu(&bus), renderer(), ppu(&bus, &renderer){}
	void init();
	void run(bool multithread, bool testMode);

	Bus bus;
	Cpu cpu;
	Renderer renderer;
	Ppu ppu;
};

