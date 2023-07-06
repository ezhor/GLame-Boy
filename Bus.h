#include <vector>
#pragma once
class Bus
{
public:
	void load();
	unsigned char read(unsigned short location);
	unsigned short read16(unsigned short location);
	void write(unsigned short location, unsigned char value);
private:
	std::vector<char> memory;
};

