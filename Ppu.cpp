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
	}
}

void Ppu::drawTile(u8 tileX, u8 tileY)
{
	u16 tiledataLocation = VRAM_LOCATION_TILEDATA_START + bus->read16(VRAM_LOCATION_TILEMAP_START + (tileY * SCREEN_WIDTH / 8 + tileX));
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int colorPosition = ((tileY * 8 + y) * SCREEN_WIDTH + (tileX * 8 + x)) * 3;
			Color color = getPixelColor(tiledataLocation, x, y);
			renderer->texture[colorPosition] = color.r;
			renderer->texture[colorPosition + 1] = color.g;
			renderer->texture[colorPosition + 2] = color.b;
		}
	}
}

Color Ppu::getPixelColor(u16 tiledataLocation, u8 offsetX, u8 offsetY)
{
	u8 line1 = bus->read(tiledataLocation + offsetY);
	u8 line2 = bus->read(tiledataLocation + offsetY + 1);

	u8 value = bitFromByte(line1, offsetX) + bitFromByte(line2, offsetX);

	return colors[value];
}

u8 Ppu::bitFromByte(u8 byte, u8 bitPosition)
{
	return (byte >> 8 - bitPosition) & 0x01;
}
