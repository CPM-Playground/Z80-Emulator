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
#include "z80_registers.h"

int main() {

    std::cout << "Z80 Emulator\n";

    try {

        
        const z80::memory<0x1000, 0x10FF> rom("zx81-v2.rom");
        std::cout << std::format("address ${:04X} .. ${:04X} size {} bytes\n", rom.address_begin(), rom.address_end(), rom.size());
        rom.dump();
        //rom.save("zx81-v2.copy");
        

        z80::regs.byte(2) = 'A';
        z80::regs.byte(3) = 'B';
        std::cout << z80::regs.byte(2) << ' ' << z80::regs.byte(3) << ' ' << std::hex << z80::regs.word(2) << '\n';
        z80::regs.word(2) = 0x4443;
        std::cout << z80::regs.byte(2) << ' ' << z80::regs.byte(3) << ' ' << std::hex << z80::regs.word(2) << '\n';
        _A = 'E';
        _F = 'F';
        std::cout << _A << ' ' << _F << ' ' << _AF << '\n';
        _AF = 0x4847;
        std::cout << _A << ' ' << _F << ' ' << _AF << '\n';
        
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

}