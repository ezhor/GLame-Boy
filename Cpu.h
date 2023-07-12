#pragma once
#include "Registers.h"
#include "Bus.h"
#include <map>
#include <functional>

#define NO_FLAG 0b00000000
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
	Cpu(Bus* bus);
	void loadInstructions();
	bool tick();
private:
	Registers registers;
	Bus* bus;
	std::map<u16, Instruction> instructions;

	u8 immediateData();
	u16 immediateData16();
	void cp(u8 value);
	void sub(u8 value);
	void logicOr(u8 value);
	void jp(u8 flag, bool opposite);
	void jp(u8 flag);
};

