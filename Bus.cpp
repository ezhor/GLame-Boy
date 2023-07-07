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

unsigned char Bus::read(unsigned short location)
{
	return memory.at(location);
}

unsigned short Bus::read16(unsigned short location)
{
	return (memory.at(location + 1) << 8) + memory.at(location);
}

void Bus::write(unsigned short location, unsigned char value)
{
	memory.at(location) = value;
}
