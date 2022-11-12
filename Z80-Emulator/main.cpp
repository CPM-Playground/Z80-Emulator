/**

    @file      main.cpp
    @brief     Z80 Emulator 
    @details   ~
    @author    ifknot
    @date      11.11.2022
    @copyright © ifknot, 2022. All right reserved.

**/
#include <iostream>
#include <exception>

#include "memory.h"

int main() {

    std::cout << "Z80 Emulator\n ";

    z80::memory<0x0000, 0x03FF> ram;

    try {

        std::cout << ram.size() << " bytes\n";

        ram.fill(0x0010, 0x0030, '!');

        ram[17] = 'A';

        std::cout << ram[17] << '\n';

        ram.dump(0x0000, 0x00FF);
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

}