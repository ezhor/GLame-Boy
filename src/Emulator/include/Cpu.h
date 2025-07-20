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
#define LOWER_BYTE 0b0000000011111111

class Cpu
{
	struct Instruction {
		int lenght = 0;
		int cyclesJump = 0;
		int cyclesDefault = 0;
		std::function<void()> implementation;
	};

public:
	Cpu(Bus* bus);

	inline static int instances = 0;
	bool verbose = false;
	Registers registers;
	Bus* bus;

	void loadInstructions();
	void tick();
	bool isRunning();
	u16 instructionsCount();
	bool interruptsEnabled();
	void setInterrupts(bool value);
private:
	Instruction instructions[512];
	bool running = true;
	bool interrupts = true;
	bool jumped = false;
	u16 cbOffset = 0;

	u8 immediateData();
	u16 immediateData16();
	
	signed char twosComplement(u8 value);
	u16 signExtension(u8 value);

	void cp(u8 value);

	u8 increment(u8 value);
	u16 increment16(u16 value);
	u8 decrement(u8 value);

	u16 add16(u16 a, u16 b);

	void logicOr(u8 value);
	void logicAnd(u8 value);
	void logicXor(u8 value);

	u8 rotateRight(u8 value);

	void jump(u8 flag, bool opposite);
	void jump(u8 flag);
	void jumpRelative(u8 flag, bool opposite);
	void jumpRelative(u8 flag);

	u16 pop();
	void push(u16 value);
	void call(u8 flag, bool opposite);
	void call(u8 flag);
	void ret(u8 flag, bool opposite);
	void ret(u8 flag);
	void reti();

	void complementAccumulator();
	void complementCarryFlag();

	u8 swap(u8 value);
};

