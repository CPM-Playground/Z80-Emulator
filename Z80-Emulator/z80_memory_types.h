/**

    @file      memory_types.h
    @brief     
    @details   ~
    @author    ifknot
    @date      12.11.2022
    @copyright © ifknot, 2022. All right reserved.

**/
#pragma once

#include <cstdint>

// Z80 is little-endian i.e. stores the least-significant byte at the smallest address
#define HI 1
#define LO 0

namespace z80 {

    using byte_t = int8_t;
    using word_t = int16_t;
    using address_t = uint16_t;

}