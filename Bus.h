#include <vector>
#include "Common.h"
#pragma once
class Bus
{
public:
	Bus() {
		instances++;
	}

	inline static int instances = 0;

	void load(const char*);
	u8 read(u16 location);
	u16 read16(u16 location);
	void write(u16 location, u8 value);
	void write16(u16 location, u16 value);
	bool updateVram;
	void printMemory(u16 location, u16 bytesCount);
	void printTilemapMemory();
private:
	char memory[0x10000];
};

