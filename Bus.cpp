#include "Bus.h"
#include <fstream>
#include <vector>
#include <iostream>

void Bus::load() {
	std::ifstream file("D:\\Code\\GameBoy\\1.HelloWorld\\out\\hello-world.gb", std::ios::binary | std::ios::ate);
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
