#include "Emulator.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <stdlib.h>

void Emulator::init()
{
	//bus.load("D:\\Code\\GameBoy\\1.HelloWorld\\out\\hello-world.gb");
	bus.load("D:\\Code\\tetris.gb");
	cpu.loadInstructions();
	renderer.init();
	ppu.init();
}

void Emulator::run(bool multithread, bool testMode)
{
	std::thread threadObj;
	if (multithread && !testMode) {
		threadObj = std::thread([this]() {while (!glfwWindowShouldClose(renderer.window)) { cpu.tick(); }});
	}
	if (testMode) {
		for (u16 i = 0; i < 0x460; i++)
		{
			bus.write(0x9000 + i, bus.read(0x193 + i));
		}
		for (u16 i = 0; i < 0x240; i++)
		{
			bus.write(0x9800 + i, bus.read(0x5F3 + i));
		}
		bus.updateVram = true;
	}
	while (!glfwWindowShouldClose(renderer.window)) {
		if (!multithread && !testMode) {
			cpu.tick();
		}
		ppu.tick();
		renderer.draw();
	}
	if (multithread && !testMode) {
		threadObj.join();
	}
	glfwTerminate();
}
