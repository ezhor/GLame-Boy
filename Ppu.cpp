#include "Ppu.h"
#include "Common.h"

void Ppu::init()
{
	bus->write(rLY, VBlank);
}

void Ppu::tick()
{
	if (bus->updateVram) {

	}
}
