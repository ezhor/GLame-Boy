#include "Cpu.h"

#include <iomanip>
#include <iostream>

bool jumped = false;

Cpu::Cpu(Bus *bus) {
    instances++;
    this->bus = bus;
    registers.setPC(INITIAL_PROGRAM_COUNTER);
    registers.setSP(INITIAL_STACK_POINTER);
}

bool Cpu::isRunning() {
    return running;
}

u8 Cpu::immediateData() {
    return bus->read(registers.getPC() + 1);
}

u16 Cpu::immediateData16() {
    return bus->read16(registers.getPC() + 1);
}

signed char Cpu::twosComplement(u8 value) {
    signed char signedValue = value;
    return value + 2;
}

void Cpu::cp(u8 value) {
    registers.setFlag(Z_FLAG, registers.getA() == value);
    registers.setFlag(N_FLAG, true);
    registers.setFlag(H_FLAG, (registers.getA() & LOWER_NIBBLE) < (value & LOWER_NIBBLE));
    registers.setFlag(C_FLAG, registers.getA() < value);
}

u8 Cpu::increment(u8 value) {
    u8 previousValue = value;
    value++;
    registers.setFlag(Z_FLAG, value == 0);
    registers.setFlag(N_FLAG, false);
    registers.setFlag(H_FLAG, (value & LOWER_NIBBLE) < (previousValue & LOWER_NIBBLE));
    return value;
}

u16 Cpu::increment16(u16 value) {
    u16 previousValue = value;
    value++;
    registers.setFlag(Z_FLAG, value == 0);
    registers.setFlag(N_FLAG, false);
    registers.setFlag(H_FLAG, (value & LOWER_BYTE) < (previousValue & LOWER_BYTE));
    return value;
}

u8 Cpu::decrement(u8 value) {
    u8 previousValue = value;
    value--;
    registers.setFlag(Z_FLAG, value == 0);
    registers.setFlag(N_FLAG, true);
    registers.setFlag(H_FLAG, (value & LOWER_NIBBLE) > (previousValue & LOWER_NIBBLE));
    return value;
}

void Cpu::logicOr(u8 value) {
    registers.setA(registers.getA() | value);
    registers.setFlag(Z_FLAG, registers.getA() == 0);
    registers.setFlag(N_FLAG, false);
    registers.setFlag(H_FLAG, false);
    registers.setFlag(C_FLAG, false);
}

void Cpu::logicXor(u8 value) {
    registers.setA(registers.getA() ^ value);
    registers.setFlag(Z_FLAG, registers.getA() == 0);
    registers.setFlag(N_FLAG, false);
    registers.setFlag(H_FLAG, false);
    registers.setFlag(C_FLAG, false);
}

u8 Cpu::rotateRight(u8 value) {
    bool cFlag = registers.getFlag(C_FLAG);
    u8 firstBit = value & 0x1;
    value >>= 1;
    if (cFlag) {
        value += 0b10000000;
    }

    registers.setFlag(Z_FLAG, false);
    registers.setFlag(N_FLAG, false);
    registers.setFlag(H_FLAG, false);
    registers.setFlag(C_FLAG, firstBit == 0x1);
    return value;
}

void Cpu::jump(u8 flag, bool opposite) {
    if (registers.getFlag(flag) != opposite) {
        registers.setPC(immediateData16());
        jumped = true;
    }
}

void Cpu::jump(u8 flag) {
    jump(flag, false);
}

void Cpu::jumpRelative(u8 flag, bool opposite) {
    if (registers.getFlag(flag) != opposite) {
        signed char signedData = immediateData();
        registers.setPC(registers.getPC() + twosComplement(immediateData()));
        jumped = true;
    }
}

void Cpu::jumpRelative(u8 flag) {
    jumpRelative(flag, false);
}

u16 Cpu::add16(u16 a, u16 b) {
    u16 previousA = a;
    a = a + b;
    registers.setFlag(N_FLAG, false);
    registers.setFlag(H_FLAG, (a & LOWER_NIBBLE) < (previousA & LOWER_NIBBLE));
    registers.setFlag(C_FLAG, a < previousA);
    return a;
}

u16 Cpu::pop() {
    u16 value = bus->read16(registers.getSP());
    registers.incrementSP(2);
    return value;
}

void Cpu::push(u16 value) {
    registers.decrementSP(2);
    bus->write16(registers.getSP(), value);
}

void Cpu::call(u8 flag, bool opposite) {
    if (registers.getFlag(flag) != opposite) {
        push(registers.getPC() + 3);
        registers.setPC(immediateData16());
        jumped = true;
    }
}

void Cpu::call(u8 flag) {
    call(flag, false);
}

void Cpu::ret(u8 flag, bool opposite) {
    if (registers.getFlag(flag) != opposite) {
        registers.setPC(pop());
        jumped = true;
    }
}

void Cpu::ret(u8 flag) {
    ret(flag, false);
}

void Cpu::reti() {
    ret(NO_FLAG);
    interrupts = true;
}


void Cpu::loadInstructions() {
    // Hello World
    instructions[0xC3] = {3, 16, 16, [this]() { jump(NO_FLAG); }}; // JP a16
    instructions[0x3E] = {2, 8, 8, [this]() { registers.setA(immediateData()); }}; // LD A,d8
    instructions[0xEA] = {3, 16, 16, [this]() { bus->write(immediateData16(), registers.getA()); }}; // LD (a16),A
    instructions[0xFA] = {3, 16, 16, [this]() { registers.setA(bus->read(immediateData16())); }}; // LD A,(a16)
    instructions[0xFE] = {2, 8, 8, [this]() { cp(immediateData()); }}; // CP d8
    instructions[0xDA] = {3, 16, 12, [this]() { jump(C_FLAG); }}; // JP C,a16
    instructions[0x01] = {3, 12, 12, [this]() { registers.setBC(immediateData16()); }}; // LD BC,d16
    instructions[0x11] = {3, 12, 12, [this]() { registers.setDE(immediateData16()); }}; // LD DE,d16
    instructions[0x21] = {3, 12, 12, [this]() { registers.setHL(immediateData16()); }}; // LD HL,d16
    instructions[0x1A] = {1, 8, 8, [this]() { registers.setA(bus->read(registers.getDE())); }}; // LD A,(DE)
    instructions[0x22] = {1, 8, 8, [this]() { bus->write(registers.getHLI(), registers.getA()); }}; // LD (HL+),A
    instructions[0x13] = {1, 8, 8, [this]() { registers.incrementDE(); }}; // INC DE
    instructions[0x0B] = {1, 8, 8, [this]() { registers.decrementBC(); }}; // DEC BC
    instructions[0x78] = {1, 4, 4, [this]() { registers.setA(registers.getB()); }}; // LD A,B
    instructions[0xB1] = {1, 4, 4, [this]() { logicOr(registers.getC()); }}; // OR C
    instructions[0xC2] = {3, 16, 12, [this]() { jump(Z_FLAG, true); }}; // JP NZ,a16

    // Tetris
    instructions[0xAF] = {1, 4, 4, [this]() { logicXor(registers.getA()); }}; // XOR A
    instructions[0x0E] = {2, 8, 8, [this]() { registers.setC(immediateData()); }}; // LD C,d8
    instructions[0x06] = {2, 8, 8, [this]() { registers.setB(immediateData()); }}; // LD B,d8
    instructions[0x32] = {1, 8, 8, [this]() { bus->write(registers.getHLD(), registers.getA()); }}; // LD (HL-),A
    instructions[0x05] = {1, 4, 4, [this]() { registers.setB(decrement(registers.getB())); }}; // DEC B
    instructions[0x20] = {2, 12, 8, [this]() { jumpRelative(Z_FLAG, true); }}; // JR NZ,r8
    instructions[0x1D] = {1, 4, 4, [this]() { registers.setE(decrement(registers.getE())); }}; // DEC E
    instructions[0x16] = {2, 8, 8, [this]() { registers.setD(immediateData()); }}; // LD D,d8
    instructions[0x1F] = {1, 4, 4, [this]() { registers.setA(rotateRight(registers.getA())); }}; // RRA
    instructions[0x25] = {1, 4, 4, [this]() { registers.setH(decrement(registers.getH())); }}; // DEC H
    instructions[0x15] = {1, 4, 4, [this]() { registers.setD(decrement(registers.getD())); }}; // DEC D
    instructions[0xB0] = {1, 4, 4, [this]() { logicOr(registers.getB()); }}; // OR B
    instructions[0x14] = {1, 4, 4, [this]() { registers.setD(increment(registers.getD())); }}; // INC D
    instructions[0x7B] = {1, 4, 4, [this]() { registers.setA(registers.getE()); }}; // LD A,E
    instructions[0xBF] = {1, 4, 4, [this]() { cp(registers.getA()); }}; // CP A
    instructions[0x29] = {1, 8, 8, [this]() { registers.setHL(add16(registers.getHL(), registers.getHL())); }}; // ADD HL,HL
    instructions[0x19] = {1, 8, 8, [this]() { registers.setHL(add16(registers.getHL(), registers.getDE())); }}; // ADD HL,DE
    instructions[0x77] = {1, 8, 8, [this]() { bus->write(registers.getHL(), registers.getA()); }}; // LD (HL),A
    instructions[0x0D] = {1, 4, 4, [this]() { registers.setC(decrement(registers.getC())); }}; // DEC C
    instructions[0xE0] = {2, 12, 12, [this]() { bus->write(0xFF00 + immediateData(), registers.getA()); }}; // LDH (a8),A
    instructions[0xF0] = {2, 12, 12, [this]() { registers.setA(bus->read(0xFF00 + immediateData())); }}; // LDH A,(a8)
    instructions[0x36] = {2, 12, 12, [this]() { bus->write(registers.getHL(), immediateData()); }}; // LD (HL),d8
    instructions[0x31] = {3, 12, 12, [this]() { registers.setSP(immediateData16()); }}; // LD SP,d16
    instructions[0x2A] = {1, 8, 8, [this]() { registers.setA(bus->read(registers.getHLI())); }}; // LD A,(HL+)
    instructions[0xE2] = {1, 8, 8, [this]() { bus->write(0xFF00 + registers.getC(), registers.getA()); }}; // LDH (C), A
    instructions[0x0C] = {1, 4, 4, [this]() { registers.setC(increment(registers.getC())); }}; // INC C

    // POP
    instructions[0xC1] = {1, 12, 12, [this]() { registers.setBC(pop()); }}; // POP BC
    instructions[0xD1] = {1, 12, 12, [this]() { registers.setDE(pop()); }}; // POP DE
    instructions[0xE1] = {1, 12, 12, [this]() { registers.setHL(pop()); }}; // POP HL
    instructions[0xF1] = {1, 12, 12, [this]() { registers.setAF(pop()); }}; // POP AF

    // PUSH
    instructions[0xC5] = {1, 16, 16, [this]() { push(registers.getBC()); }}; // PUSH BC
    instructions[0xD5] = {1, 16, 16, [this]() { push(registers.getDE()); }}; // PUSH DE
    instructions[0xE5] = {1, 16, 16, [this]() { push(registers.getHL()); }}; // PUSH HL
    instructions[0xF5] = {1, 16, 16, [this]() { push(registers.getAF()); }}; // PUSH AF

    // CALL
    instructions[0xC4] = {3, 24, 12, [this]() { call(Z_FLAG, true); }}; // CALL NZ,a16
    instructions[0xCC] = {3, 24, 12, [this]() { call(Z_FLAG); }}; // CALL Z,a16
    instructions[0xCD] = {3, 24, 12, [this]() { call(NO_FLAG); }}; // CALL a16
    instructions[0xD4] = {3, 24, 12, [this]() { call(C_FLAG, true); }}; // CALL NC,a16
    instructions[0xDC] = {3, 24, 12, [this]() { call(C_FLAG); }}; // CALL C,a16

    // RET
    instructions[0xC0] = {1, 20, 8, [this]() { ret(Z_FLAG, true); }}; // RET NZ
    instructions[0xC8] = {1, 20, 8, [this]() { ret(Z_FLAG); }}; // RET Z
    instructions[0xC9] = {1, 16, 16, [this]() { ret(NO_FLAG); }}; // RET
    instructions[0xD0] = {1, 20, 8, [this]() { ret(C_FLAG, true); }}; // RET NC
    instructions[0xD8] = {1, 20, 8, [this]() { ret(C_FLAG); }}; // RET C
    instructions[0xD9] = {1, 16, 16, [this]() { reti(); }}; // RETI

    // CONTROL
    instructions[0x00] = {1, 4, 4, []() { ; }}; // NOP
    instructions[0xF3] = {1, 4, 4, [this]() { interrupts = false; }}; // DI
    instructions[0xFB] = {1, 4, 4, [this]() { interrupts = true; }}; // EI

    // COMPLEMENT
    instructions[0x2F] = {1, 4, 4, [this]() { registers.setA(~registers.getA()); }}; // CPL
    instructions[0x3F] = {1, 4, 4, [this]() { registers.setFlag(C_FLAG, !registers.getFlag(C_FLAG)); }}; // CCF

    if (verbose) {
        std::cout << instructionsCount() << "/512 instructions implemented" << std::endl;
    }
}

u16 Cpu::instructionsCount() {
    u16 count = 0;
    for (u16 i = 0; i < sizeof(instructions) / sizeof(instructions[0]); i++) {
        if (instructions[i].implementation != nullptr) {
            count++;
        }
    }
    return count;
}

bool Cpu::interruptsEnabled() {
    return interrupts;
}

void Cpu::setInterrupts(bool value) {
    interrupts = value;
}

void Cpu::tick() {
    if (running) {
        u8 opcode = bus->read(registers.getPC());
        Instruction instruction = instructions[opcode];

        if (instruction.implementation != nullptr) {
            if (verbose) {
                std::cout
                    << "0x" << std::setfill('0') << std::setw(4) << std::hex << (unsigned int)registers.getPC()
                    << ": 0x" << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) opcode
                    << std::endl;
            }

            instruction.implementation();
            if (jumped) {
                jumped = false;
            } else {
                registers.incrementPC(instruction.lenght);
            }
        } else {
            running = false;
            std::cout << std::endl
                    << "ERROR: INSTRUCTION NOT IMPLEMENTED (0x"
                    << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << (unsigned int) registers.getPC()
                    << ": 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << (unsigned int) opcode
                    << ")" << std::endl;
        }
    }
}
