/**

    @file      emu_registers.h
    @brief     
    @details  
    @author    ifknot
    @date      15.11.2022
    @copyright © ifknot, 2022. All right reserved.

**/

#pragma once

#include <array>
#include <cstdint>
#include <format>
#include <iostream>

namespace emu {

    template<size_t SIZE>
    class registers_t final {

        using register_array_t = int8_t[SIZE];

    public:

        inline int8_t& byte(size_t i) {
            return sram[i];
        }

        inline int16_t& word(size_t i) {
            return *(int16_t*)(sram + i);
        }

        void dump_registers() {

        }

        void dump_flags() {
            std::cout << std::format("\nSZ H PNC\n{:08b}", flags());
        }

    private:

        inline uint8_t flags() const {
            return sram[0];
        }

        register_array_t sram;  // Z80 CPU's registers are implemented using static RAM.

    };

}