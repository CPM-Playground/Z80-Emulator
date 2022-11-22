#pragma once

#include <cassert>
#include <iostream>

#include "z80_registers.h"

#define _F  z80.byte(F)

namespace test_flags {

	bool run(bool verbose = false) {

		std::cout << "test Z80 flags...";

        emu::z80_registers_t z80{}; 

        if(verbose) z80.dump_flags();
        _F = 0;
        if(verbose) z80.dump_flags();
        _F |= CARRY;
        if(verbose) z80.dump_flags();
        assert(_F == 0b00000001);
        _F &= ~CARRY;
        if (verbose) z80.dump_flags();
        assert(_F == 0b00000000);
        _F |= NEGATE;
        if(verbose) z80.dump_flags();
        assert(_F == 0b00000010);
        _F &= ~NEGATE;       
        if(verbose) z80.dump_flags();
        assert(_F == 0b00000000);
        _F |= PARITY_OVERFLOW;
        if(verbose) z80.dump_flags();
        assert(_F == 0b00000100);
        _F &= ~PARITY_OVERFLOW;
        if(verbose) z80.dump_flags();
        assert(_F == 0b00000000);
        _F |= HALF_CARRY;
        if(verbose) z80.dump_flags();
        assert(_F == 0b00010000);
        _F &= ~HALF_CARRY;
        if(verbose) z80.dump_flags();
        assert(_F == 0b00000000);
        _F |= ZERO;
        if(verbose) z80.dump_flags();
        assert(_F == 0b01000000);
        _F &= ~ZERO;
        if(verbose) z80.dump_flags();
        assert(_F == 0b00000000);
        _F |= SIGN;
        if(verbose) z80.dump_flags();
        assert(_F == (int8_t)0b10000000);
        _F &= ~SIGN;
        assert(_F == 0b00000000);
        if(verbose) z80.dump_flags();
        _F |= CARRY | NEGATE | PARITY_OVERFLOW | HALF_CARRY | ZERO | SIGN;
        if (verbose) z80.dump_flags();
        assert(_F == (int8_t)0b011010111);
        
        

        return true; 

	}

}