#include "Cpu.h"
#include <iostream>
#include <iomanip>


Cpu::Cpu()
{
	bus.load();
	registers.setPC(0x100);
}

void Cpu::loadInstructions()
{
	instructions.insert({ (unsigned short)0x00, {1, []() {;}} }); // nop
	instructions.insert({ (unsigned short)0xC3, {3, [this]() {registers.setPC(bus.read16(registers.getPC() + 1));}} }); // jp a16
	instructions.insert({ (unsigned short)0x3E, {2, [this]() {registers.setA(bus.read(registers.getPC() + 1));}} }); // ld A,d8
	instructions.insert({ (unsigned short)0xEA, {3, [this]() {bus.write(bus.read16(registers.getPC() + 1), registers.getA());}}}); // ld (a16),A

	std::cout << instructions.size() << "/512 instructions implemented" << std::endl;
}



bool Cpu::tick()
{
	unsigned char opcode = bus.read(registers.getPC());

	std::map<unsigned short, Instruction>::iterator iterator = instructions.find(opcode);

	if (iterator != instructions.end()) {
		unsigned short beforeInstructionPC = registers.getPC();
		Instruction instruction = instructions.at(opcode);

		instruction.implementation();
		if (beforeInstructionPC == registers.getPC()) {
			registers.incrementPC(instruction.lenght);
		}
		return true;
	}
	else {
		std::cout << "Instruction 0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)opcode << " not implemented" << std::endl;
		return false;
	}
}