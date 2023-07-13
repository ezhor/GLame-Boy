#include "Emulator.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <stdlib.h>

void Emulator::run()
{
	std::thread threadObj([this]() {while (!glfwWindowShouldClose(renderer.window)) { cpu.tick(); }});
	while (!glfwWindowShouldClose(renderer.window)) {
		//cpu.tick();
		ppu.tick();
		renderer.draw();
	}
	threadObj.join();
	glfwTerminate();
}
