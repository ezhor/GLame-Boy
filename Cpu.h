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
	void tick();
	bool isRunning();
private:
	Registers registers;
	Bus* bus;
	Instruction instructions[512];
	bool running = true;

	u16 instructionsCount();
	u8 immediateData();
	u16 immediateData16();
	void cp(u8 value);
	u8 decrement(u8 value);
	void logicOr(u8 value);
	void logicXor(u8 value);
	u8 rotateRight(u8 value);
	void jump(u8 flag, bool opposite);
	void jump(u8 flag);
	void jumpRelative(u8 flag, bool opposite);
	void jumpRelative(u8 flag);
};

