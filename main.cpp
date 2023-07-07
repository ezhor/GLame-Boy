#include "Renderer.h"
#include "Bus.h"
#include "Cpu.h"

int main() {
	//Renderer renderer = Renderer();
	//renderer.run();
	Cpu cpu = Cpu();
	cpu.loadInstructions();
	while (cpu.tick());
}