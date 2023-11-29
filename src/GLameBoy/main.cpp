#include "Emulator.h"

int main() {
	Emulator emulator = Emulator();
	emulator.init();
	emulator.run(true, false);
}