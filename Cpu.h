#pragma once
#include "Registers.h"
#include "Bus.h"
#include <map>
#include <functional>

class Cpu
{
	struct Instruction {
		int lenght = 0;
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
};

