#include "Renderer.h"
#include "Bus.h"
#include "Cpu.h"

int main() {
	//Bus bus = Bus();
	//Renderer renderer = Renderer();
	Cpu cpu = Cpu();
	cpu.loadInstructions();
	while (cpu.tick());

	//bus.load();
	//renderer.run();
}