#include "Cpu.h"

#include <iomanip>
#include <iostream>

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
    return signedValue + 2;
}

u16 Cpu::signExtension(u8 value) {
    signed char signed_value = static_cast<signed char>(value);
    return static_cast<u16>(signed_value);
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

void Cpu::logicAnd(u8 value) {
    registers.setA(registers.getA() & value);
    registers.setFlag(Z_FLAG, registers.getA() == 0);
    registers.setFlag(N_FLAG, false);
    registers.setFlag(H_FLAG, true);
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

void Cpu::complementAccumulator() {
    registers.setA(~registers.getA());

    registers.setFlag(N_FLAG, true);
    registers.setFlag(H_FLAG, true);
}

void Cpu::complementCarryFlag() {
    registers.setFlag(C_FLAG, !registers.getFlag(C_FLAG));

    registers.setFlag(N_FLAG, false);
    registers.setFlag(H_FLAG, false);
}

u8 Cpu::swap(u8 value)
{
    u8 resultHigherNibble = value & LOWER_NIBBLE;
    u8 resultLowerNibble = value >> 4;
    u8 result = (resultHigherNibble << 4) + resultLowerNibble;

    registers.setFlag(Z_FLAG, result == 0);
    registers.setFlag(N_FLAG, false);
    registers.setFlag(H_FLAG, false);
    registers.setFlag(C_FLAG, false);

    return result;
}

void Cpu::loadInstructions() {
    // Hello World
    instructions[0xC3] = {3, 16, 16, [this]() { jump(NO_FLAG); }}; // JP a16
    instructions[0xFE] = {2, 8, 8, [this]() { cp(immediateData()); }}; // CP d8
    instructions[0xDA] = {3, 16, 12, [this]() { jump(C_FLAG); }}; // JP C,a16
    instructions[0x13] = {1, 8, 8, [this]() { registers.incrementDE(); }}; // INC DE
    instructions[0x0B] = {1, 8, 8, [this]() { registers.decrementBC(); }}; // DEC BC
    instructions[0xB1] = {1, 4, 4, [this]() { logicOr(registers.getC()); }}; // OR C
    instructions[0xC2] = {3, 16, 12, [this]() { jump(Z_FLAG, true); }}; // JP NZ,a16

    // Tetris
    instructions[0xAF] = {1, 4, 4, [this]() { logicXor(registers.getA()); }}; // XOR A
    instructions[0x05] = {1, 4, 4, [this]() { registers.setB(decrement(registers.getB())); }}; // DEC B
    instructions[0x20] = {2, 12, 8, [this]() { jumpRelative(Z_FLAG, true); }}; // JR NZ,r8
    instructions[0x1D] = {1, 4, 4, [this]() { registers.setE(decrement(registers.getE())); }}; // DEC E
    instructions[0x1F] = {1, 4, 4, [this]() { registers.setA(rotateRight(registers.getA())); }}; // RRA
    instructions[0x25] = {1, 4, 4, [this]() { registers.setH(decrement(registers.getH())); }}; // DEC H
    instructions[0x15] = {1, 4, 4, [this]() { registers.setD(decrement(registers.getD())); }}; // DEC D
    instructions[0xB0] = {1, 4, 4, [this]() { logicOr(registers.getB()); }}; // OR B
    instructions[0x14] = {1, 4, 4, [this]() { registers.setD(increment(registers.getD())); }}; // INC D
    instructions[0xBF] = {1, 4, 4, [this]() { cp(registers.getA()); }}; // CP A
    instructions[0x29] = {1, 8, 8, [this]() { registers.setHL(add16(registers.getHL(), registers.getHL())); }}; // ADD HL,HL
    instructions[0x19] = {1, 8, 8, [this]() { registers.setHL(add16(registers.getHL(), registers.getDE())); }}; // ADD HL,DE
    instructions[0x0D] = {1, 4, 4, [this]() { registers.setC(decrement(registers.getC())); }}; // DEC C
    instructions[0x0C] = {1, 4, 4, [this]() { registers.setC(increment(registers.getC())); }}; // INC C

    // LD

    instructions[0x01] = {3, 12, 12, [this]() { registers.setBC(immediateData16()); }}; // LD BC,d16
    instructions[0x11] = {3, 12, 12, [this]() { registers.setDE(immediateData16()); }}; // LD DE,d16
    instructions[0x21] = {3, 12, 12, [this]() { registers.setHL(immediateData16()); }}; // LD HL,d16
    instructions[0x31] = {3, 12, 12, [this]() { registers.setSP(immediateData16()); }}; // LD SP,d16

    instructions[0x02] = {1, 8, 8, [this]() { bus->write(registers.getBC(), registers.getA()); }}; // LD (BC),A
    instructions[0x12] = {1, 8, 8, [this]() { bus->write(registers.getDE(), registers.getA()); }}; // LD (DE),A
    instructions[0x22] = {1, 8, 8, [this]() { bus->write(registers.getHLI(), registers.getA()); }}; // LD (HL+),A
    instructions[0x32] = {1, 8, 8, [this]() { bus->write(registers.getHLD(), registers.getA()); }}; // LD (HL-),A

    instructions[0x06] = {2, 8, 8, [this]() { registers.setB(immediateData()); }}; // LD B,d8
    instructions[0x16] = {2, 8, 8, [this]() { registers.setD(immediateData()); }}; // LD D,d8
    instructions[0x26] = {2, 8, 8, [this]() { registers.setH(immediateData()); }}; // LD H,d8
    instructions[0x36] = {2, 12, 12, [this]() { bus->write(registers.getHL(), immediateData()); }}; // LD (HL),d8

    instructions[0x08] = {3, 20, 20, [this]() { bus->write16(immediateData16(), registers.getSP()); }}; // LD (a16),SP

    instructions[0x0A] = {1, 8, 8, [this]() { registers.setA(bus->read(registers.getBC())); }}; // LD A,(BC)
    instructions[0x1A] = {1, 8, 8, [this]() { registers.setA(bus->read(registers.getDE())); }}; // LD A,(DE)
    instructions[0x2A] = {1, 8, 8, [this]() { registers.setA(bus->read(registers.getHLI())); }}; // LD A,(HL+)
    instructions[0x3A] = {1, 8, 8, [this]() { registers.setA(bus->read(registers.getHLD())); }}; // LD A,(HL-)

    instructions[0x0E] = {2, 8, 8, [this]() { registers.setC(immediateData()); }}; // LD C,d8
    instructions[0x1E] = {2, 8, 8, [this]() { registers.setE(immediateData()); }}; // LD E,d8
    instructions[0x2E] = {2, 8, 8, [this]() { registers.setL(immediateData()); }}; // LD L,d8
    instructions[0x3E] = {2, 8, 8, [this]() { registers.setA(immediateData()); }}; // LD A,d8

    instructions[0x40] = {1, 4, 4, [this]() { registers.setB(registers.getB()); }}; // LD B,B
    instructions[0x41] = {1, 4, 4, [this]() { registers.setB(registers.getC()); }}; // LD B,C
    instructions[0x42] = {1, 4, 4, [this]() { registers.setB(registers.getD()); }}; // LD B,D
    instructions[0x43] = {1, 4, 4, [this]() { registers.setB(registers.getE()); }}; // LD B,E
    instructions[0x44] = {1, 4, 4, [this]() { registers.setB(registers.getH()); }}; // LD B,H
    instructions[0x45] = {1, 4, 4, [this]() { registers.setB(registers.getL()); }}; // LD B,L
    instructions[0x46] = {1, 8, 8, [this]() { registers.setB(bus->read(registers.getHL())); }}; // LD B,(HL)
    instructions[0x47] = {1, 4, 4, [this]() { registers.setB(registers.getA()); }}; // LD B,A

    instructions[0x48] = {1, 4, 4, [this]() { registers.setC(registers.getB()); }}; // LD C,B
    instructions[0x49] = {1, 4, 4, [this]() { registers.setC(registers.getC()); }}; // LD C,C
    instructions[0x4A] = {1, 4, 4, [this]() { registers.setC(registers.getD()); }}; // LD C,D
    instructions[0x4B] = {1, 4, 4, [this]() { registers.setC(registers.getE()); }}; // LD C,E
    instructions[0x4C] = {1, 4, 4, [this]() { registers.setC(registers.getH()); }}; // LD C,H
    instructions[0x4D] = {1, 4, 4, [this]() { registers.setC(registers.getL()); }}; // LD C,L
    instructions[0x4E] = {1, 8, 8, [this]() { registers.setC(bus->read(registers.getHL())); }}; // LD C,(HL)
    instructions[0x4F] = {1, 4, 4, [this]() { registers.setC(registers.getA()); }}; // LD C,A

    instructions[0x50] = {1, 4, 4, [this]() { registers.setD(registers.getB()); }}; // LD D,B
    instructions[0x51] = {1, 4, 4, [this]() { registers.setD(registers.getC()); }}; // LD D,C
    instructions[0x52] = {1, 4, 4, [this]() { registers.setD(registers.getD()); }}; // LD D,D
    instructions[0x53] = {1, 4, 4, [this]() { registers.setD(registers.getE()); }}; // LD D,E
    instructions[0x54] = {1, 4, 4, [this]() { registers.setD(registers.getH()); }}; // LD D,H
    instructions[0x55] = {1, 4, 4, [this]() { registers.setD(registers.getL()); }}; // LD D,L
    instructions[0x56] = {1, 8, 8, [this]() { registers.setD(bus->read(registers.getHL())); }}; // LD D,(HL)
    instructions[0x57] = {1, 4, 4, [this]() { registers.setD(registers.getA()); }}; // LD D,A

    instructions[0x58] = {1, 4, 4, [this]() { registers.setE(registers.getB()); }}; // LD E,B
    instructions[0x59] = {1, 4, 4, [this]() { registers.setE(registers.getC()); }}; // LD E,C
    instructions[0x5A] = {1, 4, 4, [this]() { registers.setE(registers.getD()); }}; // LD E,D
    instructions[0x5B] = {1, 4, 4, [this]() { registers.setE(registers.getE()); }}; // LD E,E
    instructions[0x5C] = {1, 4, 4, [this]() { registers.setE(registers.getH()); }}; // LD E,H
    instructions[0x5D] = {1, 4, 4, [this]() { registers.setE(registers.getL()); }}; // LD E,L
    instructions[0x5E] = {1, 8, 8, [this]() { registers.setE(bus->read(registers.getHL())); }}; // LD E,(HL)
    instructions[0x5F] = {1, 4, 4, [this]() { registers.setE(registers.getA()); }}; // LD E,A

    instructions[0x60] = {1, 4, 4, [this]() { registers.setH(registers.getB()); }}; // LD H,B
    instructions[0x61] = {1, 4, 4, [this]() { registers.setH(registers.getC()); }}; // LD H,C
    instructions[0x62] = {1, 4, 4, [this]() { registers.setH(registers.getD()); }}; // LD H,D
    instructions[0x63] = {1, 4, 4, [this]() { registers.setH(registers.getE()); }}; // LD H,E
    instructions[0x64] = {1, 4, 4, [this]() { registers.setH(registers.getH()); }}; // LD H,H
    instructions[0x65] = {1, 4, 4, [this]() { registers.setH(registers.getL()); }}; // LD H,L
    instructions[0x66] = {1, 8, 8, [this]() { registers.setH(bus->read(registers.getHL())); }}; // LD H,(HL)
    instructions[0x67] = {1, 4, 4, [this]() { registers.setH(registers.getA()); }}; // LD H,A

    instructions[0x68] = {1, 4, 4, [this]() { registers.setL(registers.getB()); }}; // LD L,B
    instructions[0x69] = {1, 4, 4, [this]() { registers.setL(registers.getC()); }}; // LD L,C
    instructions[0x6A] = {1, 4, 4, [this]() { registers.setL(registers.getD()); }}; // LD L,D
    instructions[0x6B] = {1, 4, 4, [this]() { registers.setL(registers.getE()); }}; // LD L,E
    instructions[0x6C] = {1, 4, 4, [this]() { registers.setL(registers.getH()); }}; // LD L,H
    instructions[0x6D] = {1, 4, 4, [this]() { registers.setL(registers.getL()); }}; // LD L,L
    instructions[0x6E] = {1, 8, 8, [this]() { registers.setL(bus->read(registers.getHL())); }}; // LD L,(HL)
    instructions[0x6F] = {1, 4, 4, [this]() { registers.setL(registers.getA()); }}; // LD L,A

    instructions[0x70] = {1, 8, 8, [this]() { bus->write(registers.getHL(), registers.getB()); }}; // LD (HL),B
    instructions[0x71] = {1, 8, 8, [this]() { bus->write(registers.getHL(), registers.getC()); }}; // LD (HL),C
    instructions[0x72] = {1, 8, 8, [this]() { bus->write(registers.getHL(), registers.getD()); }}; // LD (HL),D
    instructions[0x73] = {1, 8, 8, [this]() { bus->write(registers.getHL(), registers.getE()); }}; // LD (HL),E
    instructions[0x74] = {1, 8, 8, [this]() { bus->write(registers.getHL(), registers.getH()); }}; // LD (HL),H
    instructions[0x75] = {1, 8, 8, [this]() { bus->write(registers.getHL(), registers.getL()); }}; // LD (HL),L
    instructions[0x77] = {1, 8, 8, [this]() { bus->write(registers.getHL(), registers.getA()); }}; // LD (HL),A

    instructions[0x78] = {1, 4, 4, [this]() { registers.setA(registers.getB()); }}; // LD A,B
    instructions[0x79] = {1, 4, 4, [this]() { registers.setA(registers.getC()); }}; // LD A,C
    instructions[0x7A] = {1, 4, 4, [this]() { registers.setA(registers.getD()); }}; // LD A,D
    instructions[0x7B] = {1, 4, 4, [this]() { registers.setA(registers.getE()); }}; // LD A,E
    instructions[0x7C] = {1, 4, 4, [this]() { registers.setA(registers.getH()); }}; // LD A,H
    instructions[0x7D] = {1, 4, 4, [this]() { registers.setA(registers.getL()); }}; // LD A,L
    instructions[0x7E] = {1, 8, 8, [this]() { registers.setA(bus->read(registers.getHL())); }}; // LD A,(HL)
    instructions[0x7F] = {1, 4, 4, [this]() { registers.setA(registers.getA()); }}; // LD A,A

    instructions[0xE0] = {2, 12, 12, [this]() { bus->write(HRAM_LOCAITON_START + immediateData(), registers.getA()); }}; // LDH (a8),A
    instructions[0xF0] = {2, 12, 12, [this]() { registers.setA(bus->read(HRAM_LOCAITON_START + immediateData())); }}; // LDH A,(a8)

    instructions[0xE2] = {2, 8, 8, [this]() { bus->write(HRAM_LOCAITON_START + registers.getC(), registers.getA()); }}; // LD (C),A
    instructions[0xF2] = {2, 8, 8, [this]() { bus->write(HRAM_LOCAITON_START + registers.getA(), registers.getC()); }}; // LD (A),C

    instructions[0xF8] = {2, 12, 12, [this]() { registers.setHL(registers.getSP() + signExtension(immediateData())); }}; // LD HL,SP+r8
    instructions[0xF9] = {1, 8, 8, [this]() { registers.setSP(registers.getHL()); }}; // LD SP,HL

    instructions[0xEA] = {3, 16, 16, [this]() { bus->write(immediateData16(), registers.getA()); }}; // LD (a16),A
    instructions[0xFA] = {3, 16, 16, [this]() { registers.setA(bus->read(immediateData16())); }}; // LD A,(a16)

    // AND
    instructions[0xA0] = {1, 4, 4, [this]() { logicAnd(registers.getB()); }}; // AND B
    instructions[0xA1] = {1, 4, 4, [this]() { logicAnd(registers.getC()); }}; // AND C
    instructions[0xA2] = {1, 4, 4, [this]() { logicAnd(registers.getD()); }}; // AND D
    instructions[0xA3] = {1, 4, 4, [this]() { logicAnd(registers.getE()); }}; // AND E
    instructions[0xA4] = {1, 4, 4, [this]() { logicAnd(registers.getH()); }}; // AND H
    instructions[0xA5] = {1, 4, 4, [this]() { logicAnd(registers.getL()); }}; // AND L
    instructions[0xA6] = {1, 8, 8, [this]() { logicAnd(bus->read(registers.getHL())); }}; // AND (HL)
    instructions[0xA7] = {1, 4, 4, [this]() { logicAnd(registers.getA()); }}; // AND A
    instructions[0xE6] = {2, 8, 8, [this]() { logicAnd(immediateData()); }}; // AND d8

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

    // Control
    instructions[0x00] = {1, 4, 4, []() { ; }}; // NOP
    instructions[0xF3] = {1, 4, 4, [this]() { interrupts = false; }}; // DI
    instructions[0xFB] = {1, 4, 4, [this]() { interrupts = true; }}; // EI

    // Complement
    instructions[0x2F] = {1, 4, 4, [this]() { complementAccumulator(); }}; // CPL
    instructions[0x3F] = {1, 4, 4, [this]() { complementCarryFlag(); }}; // CCF

    // CB prefix
    instructions[0xCB] = {1, 4, 4, [this]() { cbOffset = CB_PREFIX_OFFSET; }}; // CB

    // SWAP
    instructions[0x130] = {2, 8, 8, [this]() { registers.setB(swap(registers.getB())); }}; // SWAP B
    instructions[0x131] = {2, 8, 8, [this]() { registers.setC(swap(registers.getC())); }}; // SWAP C
    instructions[0x132] = {2, 8, 8, [this]() { registers.setD(swap(registers.getD())); }}; // SWAP D
    instructions[0x133] = {2, 8, 8, [this]() { registers.setE(swap(registers.getE())); }}; // SWAP E
    instructions[0x134] = {2, 8, 8, [this]() { registers.setH(swap(registers.getH())); }}; // SWAP H
    instructions[0x135] = {2, 8, 8, [this]() { registers.setL(swap(registers.getL())); }}; // SWAP L
    instructions[0x136] = {2, 16, 16, [this]() { bus->write(registers.getHL(), swap(bus->read(registers.getHL()))); }}; // SWAP (HL)
    instructions[0x137] = {2, 8, 8, [this]() { registers.setA(swap(registers.getA())); }}; // SWAP A

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
        u16 opcode = cbOffset + bus->read(registers.getPC());
        Instruction instruction = instructions[opcode];
        
        cbOffset = 0;

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
