#pragma once

#include <cassert>
#include <format>
#include <iostream>

#include "emu_memory.h"

namespace test_rom {

	bool run(bool verbose = false) {

        std::cout << "test ROM... ";

        try {
            const emu::memory<1024> rom1(0x1000);
            if (verbose) std::cout << std::format("{} bytes ${:04X} - ${:04X}", rom1.size(), rom1.address_begin(), rom1.address_end()) << '\n';
            if (verbose) rom1.dump();
            assert(rom1.size() == 0x400);
            assert(rom1.address_begin() == 0x1000);
            assert(rom1.address_end() == 0x13FF);

            const emu::memory<1024> rom2(0x2000, 'A');
            if (verbose) std::cout << std::format("{} bytes ${:04X} - ${:04X}", rom2.size(), rom2.address_begin(), rom2.address_end()) << '\n';
            if (verbose) rom2.dump();
            assert(rom2[0x2000] == 'A');

            const emu::memory<8192> rom3(0x3000, "zx81-v2.rom");
            if (verbose) std::cout << std::format("{} bytes ${:04X} - ${:04X}", rom3.size(), rom3.address_begin(), rom3.address_end()) << '\n';
            if (verbose) rom3.dump();
            rom3.save("zx81-v2.copy");
        }
        catch (std::exception& e) {
            std::cout << e.what() << '\n';
            return false;
        }    
        return true;
	}

}
