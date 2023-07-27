#include "Bus.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

void Bus::load() {
	std::ifstream file("D:\\Code\\GameBoy\\1.HelloWorld\\out\\hello-world.gb", std::ios::binary | std::ios::ate);
	//std::ifstream file("D:\\Code\\tetris.gb", std::ios::binary | std::ios::ate);
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

void Bus::printMemory(u16 location, u16 bytesCount)
{
	for (u16 i = 0; i < bytesCount; i += 20)
	{
		for (u16 j = 0; j < 20; j++) {
			std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)read(location + i + j) << ", ";
		}
		std::cout << std::endl;
	}
}

void Bus::printTilemapMemory()
{
	std::cout << "Tilemap Memory:" << std::endl;
	printMemory(VRAM_LOCATION_TILEMAP_START, (SCREEN_WIDTH / 8) * (SCREEN_HEIGHT / 8));
}
