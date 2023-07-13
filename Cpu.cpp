#include "Cpu.h"
#include <iostream>
#include <iomanip>

u16 biggestPC = 0;

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

void Cpu::logicOr(u8 value)
{
	registers.setA(registers.getA() | registers.getC());
	registers.setFlag(Z_FLAG, registers.getA() == 0);
	registers.setFlag(N_FLAG, false);
	registers.setFlag(H_FLAG, false);
	registers.setFlag(C_FLAG, false);
}

void Cpu::jp(u8 flag, bool opposite)
{
	if (registers.getFlag(flag) != opposite) {
		registers.setPC(immediateData16());
	}
}

void Cpu::jp(u8 flag)
{
	jp(flag, false);
}

void Cpu::loadInstructions()
{
	instructions.insert({ 0x00, {1, 4, []() {;}} }); // NOP
	instructions.insert({ 0xC3, {3, 16, [this]() {jp(NO_FLAG);}} }); // JP a16
	instructions.insert({ 0x3E, {2, 8, [this]() {registers.setA(immediateData());}} }); // LD A,d8
	instructions.insert({ 0xEA, {3, 16, [this]() {bus->write(immediateData16(), registers.getA());}} }); // LD (a16),A
	instructions.insert({ 0xFA, {3, 16, [this]() {registers.setA(bus->read(immediateData16()));}} }); // LD A,(a16)
	instructions.insert({ 0xFE, {2, 8, [this]() {cp(immediateData());}} }); // CP d8
	instructions.insert({ 0xDA, {3, 8, [this]() {jp(C_FLAG);}} }); // JP C,a16
	instructions.insert({ 0x01, {3, 16, [this]() {registers.setBC(immediateData16());}} }); // LD BC,d16
	instructions.insert({ 0x11, {3, 12, [this]() {registers.setDE(immediateData16());}} }); // LD DE,d16
	instructions.insert({ 0x21, {3, 12, [this]() {registers.setHL(immediateData16());}} }); // LD HL,d16
	instructions.insert({ 0x1A, {1, 8, [this]() {registers.setA(bus->read(registers.getDE()));}} }); // LD A,(DE)
	instructions.insert({ 0x22, {1, 8, [this]() {bus->write(registers.getHLI(), registers.getA());}} }); // LD (HL+),A
	instructions.insert({ 0x13, {1, 8, [this]() {registers.incrementDE();}} }); // INC DE
	instructions.insert({ 0x0B, {1, 8, [this]() {registers.decrementBC();}} }); // DEC BC
	instructions.insert({ 0x78, {1, 4, [this]() {registers.setA(registers.getB());}} }); // LD A,B
	instructions.insert({ 0xB1, {1, 4, [this]() {logicOr(registers.getC());}} }); // OR C
	instructions.insert({ 0xC2, {3, 16, [this]() {jp(Z_FLAG, true);}} }); // JP NZ,a16

	std::cout << instructions.size() << "/512 instructions implemented" << std::endl;
}



void Cpu::tick()
{
	u8 opcode = bus->read(registers.getPC());

	std::map<u16, Instruction>::iterator iterator = instructions.find(opcode);

	if (iterator != instructions.end()) {
		u16 beforeInstructionPC = registers.getPC();
		Instruction instruction = instructions.at(opcode);

		//std::cout << "Executing instruction 0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)opcode << std::endl;
//		std::cout << "PC: " << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)registers.getPC()
//			<< "\t Instruction 0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)opcode << std::endl;
		if (biggestPC < registers.getPC()) {
			biggestPC = registers.getPC();
			std::cout << "Biggest PC: " << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)biggestPC
				<< "\tInstruction 0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)opcode << std::endl;
		}
		instruction.implementation();
		if (beforeInstructionPC == registers.getPC()) {
			registers.incrementPC(instruction.lenght);
		}
		//return true;
	}
	else {
		std::cout << "Instruction 0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)opcode << " not implemented" << std::endl;
		//return false;
	}
}