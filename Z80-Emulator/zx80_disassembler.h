/**

    @file      zx80_disassembler.h
    @brief     translates machine language into ZX80 assembly language
    @details   ~
    @author    ifknot
    @date      22.11.2022
    @copyright © ifknot, 2022. All right reserved.

**/
#pragma once

#include <array>
#include <functional>
#include <ostream>

namespace emu {

    class zx80_disassembler {

        typedef std::function<void(std::ostream& out)> function_t;
        typedef std::array<function_t, 2> dictionary_t;

    public:

        template<typename T>
        void translate(T& memory) {
            (dic[0])(std::cout);
            (dic[1])(std::cout);
        }

    private:

        const dictionary_t dic {
            [&](std::ostream& out) { out << "hello"; },
            [&](std::ostream& out) { out << " world\n"; },
        };

    };

}