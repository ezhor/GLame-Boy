#include "Cpu.h"
#include <iostream>
#include <iomanip>

Cpu::Cpu(Bus* bus)
{
	this->bus = bus;
	bus->load();
	registers.setPC(0x100);
}

u8 Cpu::immediateData()
{
	return bus->read(registers.getPC() + 1);
}

u16 Cpu::immediateData16()
{
	return bus->read16(registers.getPC() + 1);
}

void Cpu::cp(u8 value) {
	registers.setFlag(Z_FLAG, registers.getA() == value);
	registers.setFlag(N_FLAG, true);
	registers.setFlag(H_FLAG, (registers.getA() & LOWER_NIBBLE) < (value & LOWER_NIBBLE));
	registers.setFlag(C_FLAG, registers.getA() < value);

}

void Cpu::sub(u8 value) {
	registers.setA(registers.getA() - value);

}

void Cpu::jp(u8 flag)
{
	if (registers.getFlag(flag)) {
		registers.setPC(immediateData16());
	}
}

void Cpu::loadInstructions()
{
	instructions.insert({ (u16)0x00, {1, 4, []() {;}} }); // nop
	instructions.insert({ (u16)0xC3, {3, 16, [this]() {jp(NO_FLAG);}} }); // jp a16
	instructions.insert({ (u16)0x3E, {2, 8, [this]() {registers.setA(immediateData());}} }); // ld A,d8
	instructions.insert({ (u16)0xEA, {3, 16, [this]() {bus->write(immediateData16(), registers.getA());}} }); // ld (a16),A
	instructions.insert({ (u16)0xFA, {3, 16, [this]() {registers.setA(bus->read(immediateData16()));}} }); // ld A,(a16)
	instructions.insert({ (u16)0xFE, {2, 8, [this]() {cp(immediateData());}} }); // cp d8
	instructions.insert({ (u16)0xDA, {2, 8, [this]() {jp(C_FLAG);}} }); // JP C,a16

	std::cout << instructions.size() << "/512 instructions implemented" << std::endl;
}



bool Cpu::tick()
{
	u8 opcode = bus->read(registers.getPC());

	std::map<u16, Instruction>::iterator iterator = instructions.find(opcode);

	if (iterator != instructions.end()) {
		u16 beforeInstructionPC = registers.getPC();
		Instruction instruction = instructions.at(opcode);

		std::cout << "Executing instruction 0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)opcode << std::endl;
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