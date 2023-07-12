#include "Emulator.h"
#include <GLFW/glfw3.h>

void Emulator::run()
{	
	while (!glfwWindowShouldClose(renderer.window) && cpu.tick()) {
		renderer.draw();
	}
	glfwTerminate();
}
