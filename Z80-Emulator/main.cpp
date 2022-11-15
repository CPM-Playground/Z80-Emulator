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

#include "z80_memory.h"

int main() {

    std::cout << "Z80 Emulator\n";

    try {

        const z80::memory<0x1000, 0x10FF> rom("zx81-v2.rom");
        std::cout << std::format("address ${:04X} .. ${:04X} size {} bytes\n", rom.address_begin(), rom.address_end(), rom.size());
        rom.dump();
        rom.save("zx81-v2.copy");

        
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

}