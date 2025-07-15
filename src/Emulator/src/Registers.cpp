#include "Registers.h"
#include <iostream>

Registers::Registers()
{
	instances++;
	af = 0;
	f = (u8*)&af;
	a = &f[1];
	bc = 0;
	de = 0;
	hl = 0;
	c = (u8*)&bc;
	b = &c[1];
	e = (u8*)&de;
	d = &e[1];
	l = (u8*)&hl;
	h = &l[1];
	sp = 0;
	pc = 0;
}

u8 Registers::getA()
{
	return *a;
}

void Registers::setA(u8 value)
{
	*a = value;
}

u8 Registers::getF()
{
	return *f;
}

void Registers::setF(u8 value)
{
	*f = value;
}

u8 Registers::getB()
{
	return *b;
}

void Registers::setB(u8 value)
{
	*b = value;
}

u8 Registers::getD()
{
	return *d;
}

void Registers::setD(u8 value)
{
	*d = value;
}

u8 Registers::getC()
{
	return *c;
}

void Registers::setC(u8 value)
{
	*c = value;
}

u8 Registers::getE()
{
	return *e;
}

void Registers::setE(u8 value)
{
	*e = value;
}

u8 Registers::getH()
{
	return *h;
}

void Registers::setH(u8 value)
{
	*h = value;
}

void Registers::setL(u8 value)
{
	*l = value;
}

u16 Registers::getAF() {
	return af;
}


void Registers::setAF(u16 value) {
	af = value;
}

u16 Registers::getBC()
{
	return bc;
}

void Registers::setBC(u16 value)
{
	bc = value;
}

void Registers::decrementBC()
{
	bc--;
}

u16 Registers::getDE()
{
	return de;
}

void Registers::setDE(u16 value)
{
	de = value;
}

void Registers::incrementDE()
{
	de++;
}

u16 Registers::getHL()
{
	return hl;
}

u16 Registers::getHLI() {
	return hl++;
}

u16 Registers::getHLD()
{
	return hl--;
}

void Registers::setHL(u16 value)
{
	hl = value;
}

u16 Registers::getSP()
{
	return sp;
}

void Registers::setSP(u16 value)
{
	sp = value;
}

u16 Registers::getPC()
{
	return pc;
}

void Registers::setPC(u16 value)
{
	pc = value;
}

void Registers::incrementPC(u16 increment)
{
	setPC(getPC() + increment);
}

void Registers::incrementPC()
{
	incrementPC(1);
}

void Registers::incrementSP(u16 increment)
{
	setSP(getSP() + increment);
}

bool Registers::getFlag(u8 flag)
{
	return (getF() & flag) == flag;
}

void Registers::setFlag(u8 flag, bool value)
{
	setF(value ? (getF() | flag) : (getF() & ~flag));
}
