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

    std::cout << "Z80 Emulator\n";

    try {

        const z80::memory<0x0000, 0x1FFF> rom("zx81.rom");
        std::cout << rom.size() << " bytes\n";
        rom.dump(0x0000, 0x01FF);

        
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

}