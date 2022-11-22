/**

    @file      main.cpp
    @brief     Z80 Emulator 
    @details   ~
    @author    ifknot
    @date      11.11.2022
    @copyright © ifknot, 2022. All right reserved.

**/

#include <array>
#include <exception>
#include <functional>
#include <iostream>

#include "test_flags.h"
#include "test_registers.h"
#include "test_rom.h"

#include "zx80_disassembler.h"

int main() {

    std::cout << "Z80 Emulator\n";

    //if(test_flags::run()) std::cout << "pass\n";
    //if(test_registers::run()) std::cout << "pass\n";
    //if(test_rom::run(true)) std::cout << "pass\n";

    const emu::memory<8192> rom(0x3000, "zx81-v2.rom");

    emu::zx80_disassembler d;

    d.translate(rom);
    
}