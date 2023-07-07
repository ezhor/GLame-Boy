#pragma once
#include "Registers.h"
#include "Bus.h"
#include <map>
#include <functional>

#define Z_FLAG 0b10000000
#define N_FLAG 0b01000000
#define H_FLAG 0b00100000
#define C_FLAG 0b00010000
#define LOWER_NIBBLE 0b00001111

class Cpu
{
	struct Instruction {
		int lenght;
		int cycles;
		std::function<void()> implementation;
	};

public:
	Cpu();
	void loadInstructions();
	bool tick();
private:
	Registers registers;
	Bus bus;
	std::map<unsigned short, Instruction> instructions;

	unsigned char immediateData();
	unsigned short immediateData16();
	void setFlag(unsigned char flag, bool value);
	void cp(unsigned char value);
	void sub(unsigned char value);
};

