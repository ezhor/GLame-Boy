#include "Bus.h"
#include "Renderer.h"

#pragma once
class Ppu
{
public:
	Ppu(Bus* bus, Renderer* renderer) {
		this->bus = bus;
		this->renderer = renderer;
	}

	void init();
	void tick();

private:
	Bus* bus;
	Renderer* renderer;
};

