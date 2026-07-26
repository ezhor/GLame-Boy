#include <iostream>
#include <ostream>

#include "Emulator.h"

int main(const int argc, char **argv) {
    if (argc > 1) {
        Emulator emulator = Emulator();
        emulator.init(argv[1]);
        emulator.run(true, false);
    } else {
        std::cout << "No ROM provided" << std::endl;
    }
}
