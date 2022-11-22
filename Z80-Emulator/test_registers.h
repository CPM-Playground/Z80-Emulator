#pragma once

#include <cassert>
#include <iostream>

#include "z80_registers.h"

#define _F  z80.byte(F)
#define _A  z80.byte(A)
#define _PSW z80.word(F)
#define _B  z80.byte(B)
#define _C  z80.byte(C)
#define _BC z80.word(B)
#define _D  z80.byte(D)
#define _E  z80.byte(E)
#define _DE z80.word(D)
#define _H  z80.byte(H)
#define _L  z80.byte(L)
#define _HL z80.word(H)
#define _I  z80.byte(I)
#define _R  z80.byte(R)
#define _SP z80.word(SP)
#define _PC z80.word(PC)
#define _IX z80.word(IX)
#define _IY z80.word(IY)

namespace test_registers {

    bool run(bool verbose = false) {

        std::cout << "test Z80 registers...";

        emu::z80_registers_t z80{};

        z80.byte(2) = 'A';
        z80.byte(3) = 'B';
        if (verbose) std::cout << z80.byte(2) << ' ' << z80.byte(3) << ' ' << std::hex << z80.word(2) << '\n';
        assert(_B == 'A');
        assert(_C == 'B');
        assert(_BC == 0x4241);
        z80.word(2) = 0x4443;
        if (verbose) std::cout << z80.byte(2) << ' ' << z80.byte(3) << ' ' << std::hex << z80.word(2) << '\n';
        assert(_B == 'C');
        assert(_C == 'D');
        _A = 'E';
        _F = 'F';
        if (verbose) std::cout << _F << ' ' << _A << ' ' << _PSW << '\n';
        assert(_F == 'F');
        assert(_A == 'E');
        assert(_PSW == 0x4546);
        _PSW = 0x4645;

        return true;
    }

}