#include "Common.h"

#pragma once
class Registers
{
public:
	Registers();
	u8 getA();
	void setA(u8 value);

	u8 getF();
	void setF(u8 value);

	u8 getB();
	void setB(u8 value);

	u8 getD();
	void setD(u8 value);

	u8 getC();
	void setC(u8 value);

	u8 getE();
	void setE(u8 value);

	u8 getH();
	void setH(u8 value);

	void setL(u8 value);

	u16 getBC();
	void setBC(u16 value);
	void decrementBC();

	u16 getDE();
	void setDE(u16 value);
	void incrementDE();

	u16 getHL();
	u16 getHLI();
	u16 getHLD();
	void setHL(u16 value);

	u16 getSP();
	void setSP(u16 value);

	u16 getPC();
	void setPC(u16 value);
	void incrementPC(u16 increment);
	void incrementPC();

	bool getFlag(u8 flag);
	void setFlag(u8 flag, bool value);

private:
	u8 a;
	u8 f;
	u8* b;
	u8* c;
	u8* d;
	u8* e;
	u8* h;
	u8* l;
	u16 bc;
	u16 de;
	u16 hl;
	u16 sp;
	u16 pc;
};

