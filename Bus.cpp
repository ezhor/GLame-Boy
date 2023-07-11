#include "Bus.h"
#include <fstream>
#include <vector>
#include <iostream>

void Bus::load() {
	std::ifstream file("D:\\Code\\GameBoy\\1.HelloWorld\\out\\hello-world.gb", std::ios::binary | std::ios::ate);
	//std::ifstream file("D:\\Media\\Downloads\\tetris.gb", std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	memory = std::vector<char>(0x10000);
	file.seekg(0, std::ios::beg);
	file.read(memory.data(), size);
}

u8 Bus::read(u16 location)
{
	return memory.at(location);
}

u16 Bus::read16(u16 location)
{
	return (memory.at(location + 1) << 8) + memory.at(location);
}

void Bus::write(u16 location, u8 value)
{
	memory.at(location) = value;
}
