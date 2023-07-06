#include "Registers.h"
#include <iostream>

Registers::Registers()
{
	a = 0;
	f = 0;
	bc = 0;
	de = 0;
	hl = 0;
	c = (unsigned char*)&bc;
	b = &c[1];
	e = (unsigned char*)&de;
	d = &e[1];
	l = (unsigned char*)&hl;
	h = &l[1];
	sp = 0;
	pc = 0;
}

unsigned char Registers::getA()
{
	return a;
}

void Registers::setA(unsigned char value)
{
	a = value;
}

unsigned char Registers::getF()
{
	return f;
}

void Registers::setF(unsigned char value)
{
	f = value;
}

unsigned char Registers::getB()
{
	return *b;
}

void Registers::setB(unsigned char value)
{
	*b = value;
}

unsigned char Registers::getC()
{
	return *c;
}

void Registers::setC(unsigned char value)
{
	*c = value;
}

unsigned char Registers::getE()
{
	return *e;
}

void Registers::setE(unsigned char value)
{
	*e = value;
}

unsigned char Registers::getH()
{
	return *h;
}

void Registers::setL(unsigned char value)
{
	*l = value;
}

unsigned short Registers::getBC()
{
	return bc;
}

void Registers::setBC(unsigned short value)
{
	bc = value;
}

unsigned short Registers::getDE()
{
	return de;
}

void Registers::setDE(unsigned short value)
{
	de = value;
}

unsigned short Registers::getHL()
{
	return hl;
}

void Registers::setHL(unsigned short value)
{
	hl = value;
}

unsigned short Registers::getSP()
{
	return sp;
}

void Registers::setSP(unsigned short value)
{
	sp = value;
}

unsigned short Registers::getPC()
{
	return pc;
}

void Registers::setPC(unsigned short value)
{
	pc = value;
}

void Registers::incrementPC(unsigned short increment)
{
	setPC(getPC() + increment);
}

void Registers::incrementPC()
{
	incrementPC(1);
}
