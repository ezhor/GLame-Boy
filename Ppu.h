#include "Bus.h"
#include "Renderer.h"

struct Color {
	u8 r; u8 g; u8 b;
	Color() {
		r = 0;
		g = 0;
		b = 0;
	}
	Color(u8 r, u8 g, u8 b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

#pragma once
class Ppu
{
public:
	Ppu(Bus* bus, Renderer* renderer) {
		this->bus = bus;
		this->renderer = renderer;
		this->colors[0] = Color(0x40, 0x50, 0x10);
		this->colors[1] = Color(0x70, 0x80, 0x28);
		this->colors[2] = Color(0xA0, 0xA8, 0x40);
		this->colors[3] = Color(0xD0, 0xD0, 0x58);
	}

	void init();
	void tick();
	void drawTile(u8 tileX, u8 tileY);
	Color getPixelColor(u16 tiledataLocation, u16 offsetX, u16 offsetY);

private:
	Bus* bus;
	Renderer* renderer;
	Color colors[4];
	u8 bitFromByte(u8 byte, u8 bitPosition);
};

