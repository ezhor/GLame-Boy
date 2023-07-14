#include "Bus.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

void Bus::load() {
	std::ifstream file("D:\\Code\\GameBoy\\1.HelloWorld\\out\\hello-world.gb", std::ios::binary | std::ios::ate);
	//std::ifstream file("D:\\Code\\GameBoy\\2.HolaMundo(TileTest)\\out\\HolaMundo.gb", std::ios::binary | std::ios::ate);
	//std::ifstream file("D:\\Media\\Downloads\\tetris.gb", std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	file.read(memory, size);
}

u8 Bus::read(u16 location)
{
	return memory[location];
}

u16 Bus::read16(u16 location)
{
	u16 highByte = memory[location + 1] << 8;
	u16 lowByte = memory[location] & 0xFF;
	return highByte + lowByte;
}

void Bus::write(u16 location, u8 value)
{
	memory[location] = value;
	if (location >= VRAM_LOCATION_START && location <= VRAM_LOCATION_END) {
		updateVram = true;
	}
}

void Bus::printVram()
{
	for (u16 i = 0; i < (SCREEN_WIDTH / 8) * (SCREEN_HEIGHT / 8); i += SCREEN_WIDTH / 8)
	{
		for (u16 j = 0; j < SCREEN_WIDTH / 8; j++) {
			std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)read(VRAM_LOCATION_TILEMAP_START + i + j) << ", ";
		}
		std::cout << std::endl;
	}
}
