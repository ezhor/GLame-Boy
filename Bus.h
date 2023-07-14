#include <vector>
#include "Common.h"
#pragma once
class Bus
{
public:
	void load();
	u8 read(u16 location);
	u16 read16(u16 location);
	void write(u16 location, u8 value);
	bool updateVram;
	void printVram();
private:
	char memory[0x10000];
};

