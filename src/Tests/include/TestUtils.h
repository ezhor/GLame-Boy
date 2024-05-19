#pragma once
#include "Emulator.h"
class TestUtils
{
public:
	static Emulator* getEmulator();
	static void testCP(u8 registerValue, u8 immediateValue, u8 flag, bool flagValue);
};