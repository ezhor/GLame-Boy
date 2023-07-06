#pragma once
class Registers
{
public:
	Registers();
	unsigned char getA();
	void setA(unsigned char value);
	unsigned char getF();
	void setF(unsigned char value);
	unsigned char getB();
	void setB(unsigned char value);
	unsigned char getC();
	void setC(unsigned char value);
	unsigned char getE();
	void setE(unsigned char value);
	unsigned char getH();
	void setL(unsigned char value);
	unsigned short getBC();
	void setBC(unsigned short value);
	unsigned short getDE();
	void setDE(unsigned short value);
	unsigned short getHL();
	void setHL(unsigned short value);
	unsigned short getSP();
	void setSP(unsigned short value);
	unsigned short getPC();
	void setPC(unsigned short value);
	void incrementPC(unsigned short increment);
	void incrementPC();

private:
	unsigned char a;
	unsigned char f;
	unsigned char* b;
	unsigned char* c;
	unsigned char* d;
	unsigned char* e;
	unsigned char* h;
	unsigned char* l;
	unsigned short bc;
	unsigned short de;
	unsigned short hl;
	unsigned short sp;
	unsigned short pc;
};

