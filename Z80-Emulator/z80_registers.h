/**

    @file      z80_registers.h
    @brief     
    @details  
    ##CPU Registers
    The Z80 CPU contains 208 bits (26 bytes) of read/write memory that are available to the programmer. 
    The table below shows how this memory is configured to eighteen 8-bit registers and four 16-bit registers. 
    All Z80 CPU's registers are implemented using static RAM. 
    The registers include two sets of six general-purpose registers that can be used individually as 8-bit registers or in pairs as 16-bit registers. 
    There are also two sets of Accumulator and Flag registers and six special-purpose registers.

        Main Register Set	Alternate Register Set
        Accumulator	Flags	Accumulator	Flags
            A	F	            A'	F'
            B	C	            B'	B'	General Purpose Registers
            D	E	            D'	E'
            H	L	            H'	L'

        Interrupt Vector
        I	Memory Refresh
        R	Special Purpose Registers
        Index Register IX
        Incex Register IY
        Stack Pointer SP
        Program Counter PC

    ##Special-Purpose Registers
    ###Program Counter (PC). 
    The program counter holds the 16-bit address of the current instruction being fetched from memory. 
    The Program Counter is automatically incremented after its contents are transferred to the address lines. When a program jump occurs, the new value is automatically placed in the Program Counter, overriding the incrementer.

    ###Stack Pointer (SP). 
    The stack pointer holds the 16-bit address of the current top of a stack located anywhere in external system RAM memory. 
    The external stack memory is organized as a last-in first-out (LIFO) file. Data can be pushed onto the stack from specific CPU registers or popped off of the stack to specific CPU registers through the execution of PUSH and POP instructions. 
    The data popped from the stack is always the most recent data pushed onto it. 
    The stack allows simple implementation of multiple level interrupts, unlimited subroutine nesting and simplification of many types of data manipulation.

    ###Two Index Registers (IX and IY). 
    The two independent index registers hold a 16-bit base address that is used in indexed addressing modes. 
    In this mode, an index register is used as a base to point to a region in memory from which data is to be stored or retrieved. 
    An additional byte is included in indexed instructions to specify a displacement from this base. This displacement is specified as a two's complement signed integer. 
    This mode of addressing greatly simplifies many types of programs, especially when tables of data are used.

    ###Interrupt Page Address (I) Register. 
    The Z80 CPU can be operated in a mode in which an indirect call to any memory location can be achieved in response to an interrupt. 
    The I register is used for this purpose and stores the high-order eight bits of the indirect address while the interrupting device provides the lower eight bits of the address. 
    This feature allows interrupt routines to be dynamically located anywhere in memory with minimal access time to the routine.

    ###Memory Refresh (R) Register. 
    The Z80 CPU contains a memory refresh counter, enabling dynamic memories to be used with the same ease as static memories. 
    Seven bits of this 8-bit register are automatically incremented after each instruction fetch. 
    The eighth bit remains as programmed, resulting from an LD R, A instruction. 
    The data in the refresh counter is sent out on the lower portion of the address bus along with a refresh control signal while the CPU is decoding and executing the fetched instruction. 
    This mode of refresh is transparent to the programmer and does not slow the CPU operation. 
    The programmer can load the R register for testing purposes, but this register is normally not used by the programmer. 
    During refresh, the contents of the I Register are placed on the upper eight bits of the address bus.

    ##Accumulator and Flag Registers. 
    The CPU includes two independent 8-bit Accumulators and associated 8-bit Flag registers. 
    The Accumulator holds the results of 8-bit arithmetic or logical operations while the Flag Register indicates specific conditions for 8-bit or 16-bit operations, such as indicating whether or not the result of an operation is equal to 0. 
    The programmer selects the Accumulator and flag pair with a single exchange instruction so that it is possible to work with either pair.

    ##General Purpose Registers
    Two matched sets of general-purpose registers, each set containing six 8-bit registers, can be used individually as 8-bit registers or as 16-bit register pairs. 
    One set is called BC, DE, and HL while the complementary set is called BC', DE', and HL'. 
    At any one time, the programmer can select either set of registers to work through a single exchange command for the entire set. 
    In systems that require fast interrupt response, one set of general-purpose registers and an Accumulator/Flag Register can be reserved for handling this fast routine. 
    One exchange command is executed to switch routines. 
    This process greatly reduces interrupt service time by eliminating the requirement for saving and retrieving register contents in the external stack during interrupt or subroutine processing. 
    These general-purpose registers are used for a wide range of applications. 
    They also simplify programming, specifically in ROM-based systems in which little external read/write memory is available.

    ##Arithmetic Logic Unit
    The 8-bit arithmetic and logical instructions of the CPU are executed in the Arithmetic Logic Unit (ALU). 
    Internally, the ALU communicates with the registers and the external data bus by using the internal data bus. 
    Functions performed by the ALU include:

        + Add
        + Subtract
        + Logical AND
        + Logical OR
        + Logical eXclusive OR
        + Compare
        + Left or right shifts or rotates (aritmetic and logical)
        + Increment
        + Decrement
        + Set bit
        + Reset bit
        + Test bit
        
    ##Instruction Register and CPU control
    As each instruction is fetched from memory, it is placed in the Instruction Register and decoded. 
    The control sections performs this function and then generates and supplies the control signals necessary to read or write data from or to the registers, control the ALU, and provide required external control signals.

    @author    ifknot
    @date      15.11.2022
    @copyright © ifknot, 2022. All right reserved.

**/

/*

#include <array>
#include <cstdint>
#include <iostream>

struct registers_t {
  
  using register_array_t = int8_t[26]; 

  int8_t& byte(size_t i) {
    return data[i];
  } 
  
  int16_t& word(size_t i) {
    return *(int16_t*)(data + i);
  }
  
  register_array_t data;
  
};

int main()  {
    
    registers_t r;
    r.byte(2) = 'A';
    r.byte(3) = 'B';
    std::cout << r.byte(2) << ' ' << r.byte(3) << ' '<< std::hex << r.word(2) << '\n';
    r.word(2) = 0x4443;
    std::cout << r.byte(2) << ' ' << r.byte(3) << ' '<< std::hex << r.word(2) << '\n';
    
}

*/

#pragma once

#include <array>
#include <iostream>
#include <memory>
#include <string>

#include "z80_memory_types.h"

#define _A   regs[af].byte[LO]
#define _F   regs[af].byte[HI]
#define _AF  regs[af].word

namespace z80 {

    union register_t {
        word_t word;
        byte_t byte[2];
    };

    enum name_t {
        // accumulator and flags
        _af = 0,  
        // general purpose registers
        _bc = 2, 
        _de = 4, 
        _hl = 6,     
        //alternate registers
        __af = 8,
        __bc = 10,
        __de = 12,
        __hl = 14,
        // special purpose regsiters
        _ix = 16,    // index x
        _iy = 18,    // index y    
        _sp = 20,    // stack pointer
        _pc = 22,    // program counter 
        __i,         // interrupt vector 
        __r          // memory refresh
    };

    using register_array_t = std::array<register_t, 26>;    //

    static register_array_t regs;

}
