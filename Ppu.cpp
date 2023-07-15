#include "Ppu.h"
#include "Common.h"
#include <iostream>

void Ppu::init()
{
	bus->write(rLY, VBlank);
}

void Ppu::tick()
{
	if (bus->updateVram) {
		bus->updateVram = false;
		for (u8 tileY = 0; tileY < SCREEN_HEIGHT / 8; tileY++) {
			for (u8 tileX = 0; tileX < SCREEN_WIDTH / 8; tileX++) {
				drawTile(tileX, tileY);
			}
		}
		renderer->sendTextureData();
		std::cout << "Tilemap ROM" << std::endl;
		bus->printMemory(0x5F3, 0x240);
		bus->printTilemapMemory();
	}
}

void Ppu::drawTile(u8 tileX, u8 tileY)
{
	u16 tiledataLocation = VRAM_LOCATION_TILEDATA_START + bus->read(VRAM_LOCATION_TILEMAP_START + (tileY * TILEMAP_WIDTH) + tileX);
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int colorPosition = ((SCREEN_HEIGHT - 1 - (tileY * 8 + y)) * SCREEN_WIDTH + (tileX * 8 + x)) * 3;
			Color color = getPixelColor(tiledataLocation, x, y);
			renderer->texture[colorPosition] = color.r;
			renderer->texture[colorPosition + 1] = color.g;
			renderer->texture[colorPosition + 2] = color.b;
		}
	}
}

Color Ppu::getPixelColor(u16 tiledataLocation, u8 offsetX, u8 offsetY)
{
	u8 line1 = bus->read(tiledataLocation + offsetY * 2);
	u8 line2 = bus->read(tiledataLocation + (offsetY * 2) + 1);

	u8 value = (u8)(bitFromByte(line1, offsetX) << 1) + bitFromByte(line2, offsetX);

	return colors[value];
}

u8 Ppu::bitFromByte(u8 byte, u8 bitPosition)
{
	return (byte >> (8 - (bitPosition + 1))) & 0x01;
}
