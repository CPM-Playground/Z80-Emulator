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

    ##Z80 Status Indicator Flags
    The Flag registers, F and F', supply information to the user about the status of the Z80 CPU at any particular time. 
    The bit positions and definitions for each flag are listed in the tables below.

        Bit	        7	6	5	4	3	2	1	0
        Position	S	Z	x	H	y	P/V	N	C

        Symbol	Field Name
        C	    Carry Flag
        N	    Add/Subtract
        P/V	    Parity/Overflow Flag
        y	    unused (3rd bit of last 8-bit instruction that altered flags)
        H	    Half Carry Flag
        x	    unused (5th bit of last 8-bit instruction that altered flags)
        Z	    Zero Flag
        S	    Sign Flag

    Each of these two Flag registers contains 6 bits of status information that are set or cleared by CPU operations; bits 3 and 5 are not used. 
    Four of these bits (C, P/V, Z, and S) can be tested for use with conditional JUMP, CALL, or RETURN instructions. 
    The H and N flags cannot be tested; these two flags are used for BCD arithmetic.

    ###Carry Flag
    The Carry Flag (C) is set or cleared depending on the operation being performed. For ADD instructions that generate a Carry, and for SUB instructions that generate a Borrow, the Carry Flag is set. The Carry Flag is reset by an ADD instruction that does not generate a Carry, and by a SUB instruction that does not generate a Borrow. This saved Carry facilitates software routines for extended precision arithmetic. Additionally, the DAA instruction sets the Carry Flag if the conditions for making the decimal adjustment are met.

    For the RLA, RRA, RLS, and RRS instructions, the Carry bit is used as a link between the least-significant byte (LSB) and the most-significant byte (MSB) for any register or memory location. During the RLCA, RLC, and SLA instructions, the Carry flag contains the final value shifted out of bit 7 of any register or memory location. During the RRCA, RRC, SRA, and SRL instructions, the Carry flag contains the final value shifted out of bit 0 of any register or memory location.

    For the logical instructions AND, OR, and XOR, the Carry flag is reset.

    The Carry flag can also be set by the Set Carry Flag (SCF) instruction and complemented by the Compliment Carry Flag (CCF) instruction.

    ###Add/Subtract Flag
    The Add/Subtract Flag (N) is used by the Decimal Adjust Accumulator instruction (DAA) to distinguish between the ADD and SUB instructions. For ADD instructions, N is cleared to 0. For SUB instructions, N is set to 1.

    ###Decimal Adjust Accumulator Flag
    The Decimal Adjust Accumulator (DAA) instruction uses this flag to distinguish between ADD and SUBTRACT instructions. For all ADD instructions, N sets to 0. For all SUBTRACT instructions, N sets to 1.

    ###Parity/Overflow Flag
    The Parity/Overflow (P/V) Flag is set to a specific state depending on the operation being performed. For arithmetic operations, this flag indicates an overflow condition when the result in the Accumulator is greater than the maximum possible number (+127) or is less than the minimum possible number (â€“128). This overflow condition is determined by examining the sign bits of the operands.

    For addition, operands with different signs never cause overflow. When adding operands with similar signs and the result contains a different sign, the Overflow Flag is set, as shown in the following example.

    +120  =  0111 1000  ADDEND
    +105  =  0110 1001  AUGEND
    ------------------------------------
    +225  =  1110 0001  (-95)    SUM
    The two numbers added together result in a number that exceeds +127 and the two positive operands result in a negative number (â€“95), which is incorrect. The Overflow Flag is therefore set.

    For subtraction, overflow can occur for operands of unalike signs. Operands of alike signs never cause overflow, as shown in the following example.

          +127  0111 1111   MINUEND
     (-)   -64  1100 0000   SUBTRAHEND
     ----------------------------------
          +191  1011 1111   DIFFERENCE
    The minuend sign has changed from a positive to a negative, resulting in an incorrect difference; the Overflow Flag is set.
    Another method for identifying an overflow is to observe the Carry to and out of the sign bit. If there is a Carry in and no Carry out, or if there is no Carry in and a Carry out, then an Overflow has occurred.
    This flag is also used with logical operations and rotate instructions to indicate the resulting parity is even.
    The number of 1 bits in a byte are counted. If the total is Odd, ODD parity is flagged (i.e., P = 0). If the total is even, even parity is flagged (i.e., P = 1).

    During the CPI, CPIR, CPD, and CPDR search instructions and the LDI, LDIR, LDD, and LDDR block transfer instructions, the P/V Flag monitors the state of the Byte Count (BC) Register.
    When decrementing, if the byte counter decrements to 0, the flag is cleared to 0; otherwise the flag is set to 1.

    During the LD A, I and LD A, R instructions, the P/V Flag is set with the value of the interrupt enable flip-flop (IFF2) for storage or testing.
    When inputting a byte from an I/O device with an IN r, (C) instruction, the P/V Flag is adjusted to indicate data parity.

    ###Half Carry Flag
    The Half Carry Flag (H) is set (1) or cleared (0) depending on the Carry and Borrow status between bits 3 and 4 of an 8-bit arithmetic operation. This flag is used by the Decimal Adjust Accumulator (DAA) instruction to correct the result of a packed BCD add or subtract operation. The H Flag is set (1) or cleared (0) as shown in the table below.

    H Flag	Add	Subtract
    1	A Carry occurs from bit 3 to bit 4	A Borrow from bit 4 occurs
    0	No Carry occurs from bit 3 to bit 4	No Borrow from bit 4 occurs
    
    ###Zero Flag
    The Zero Flag (Z) is set (1) or cleared (0) if the result generated by the execution of certain instructions is 0.
    For 8-bit arithmetic and logical operations, the Z flag is set to a 1 if the resulting byte in the Accumulator is 0. 
    If the byte is not 0, the Z flag is reset to 0.

    For Compare (search) instructions, the Z flag is set to 1 if the value in the Accumulator is equal to the value in the memory location indicated by the value of the register pair HL.

    When testing a bit in a register or memory location, the Z flag contains the complemented state of the indicated bit.

    When inputting or outputting a byte between a memory location and an INI, IND, OUTI, or OUTD I/O device, if the result of decrementing Register B is 0, then the Z flag is 1; otherwise, the Z flag is 0. Additionally, for byte inputs from I/O devices using IN r, (C), the Z flag is set to indicate a 0-byte input.

    ###Sign Flag
    The Sign Flag (S) stores the state of the most-significant bit of the Accumulator (bit 7).
    When the Z80 CPU performs arithmetic operations on signed numbers, the binary twos-complement notation is used to represent and process numeric information. 
    A positive number is identified by a 0 in Bit 7. A negative number is identified by a 1. The binary equivalent of the magnitude of a positive number is stored in bits 0 to 6 for a total range of 0 to 127.
    A negative number is represented by the twos complement of the equivalent positive number. 
    The total range for negative numbers is -1 to -128.

    @author    ifknot
    @date      15.11.2022
    @copyright © ifknot, 2022. All right reserved.

**/

#pragma once

#include <array>
#include <cstdint>
#include <iostream>

constexpr auto Z80_REGISTER_COUNT = 26;

#define _F z80::regs.byte(0)
#define _A z80::regs.byte(1)
#define _AF z80::regs.word(0)

namespace z80 {

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

        // making all the flag methods explicit to reduce errors emulating opcodes

        inline bool carry() const {
            return sram[0] & 0b00000001;
        }

        inline void set_carry() {
            flags() |= 0b000000001;
        }

        inline void clr_carry() {
            flags() &= 0b11111110;
        }

        inline bool negate() const {
            return sram[0] & 0b00000010;
        }

        inline void set_negate() {
            flags() |= 0b000000010;
        }

        inline void clr_negate() {
            flags() &= 0b11111101;
        }

        inline bool parity_overflow() const {
            return sram[0] & 0b00000100;
        }

        inline void set_parity_overflow() {
            flags() |= 0b000000100;
        }

        inline void clr_parity_overflow() {
            flags() &= 0b11111011;
        }

        inline bool half_carry() const {
            return sram[0] & 0b00010000;
        }

        inline void set_half_carry() {
            flags() |= 0b00010000;
        }

        inline void clr_half_carry() {
            flags() &= 0b11101111;
        }

        inline bool zero() const {
            return sram[0] & 0b01000000;
        }

        inline void set_zero() {
            flags() |= 0b01000000;
        }

        inline void clr_zero() {
            flags() &= 0b10111111;
        }

        inline bool sign() const {
            return sram[0] & 0b10000000;
        }

        inline void set_sign() {
            flags() |= 0b100000000;
        }

        inline void clr_sign() {
            flags() &= 0b01111111;
        }

        void dump_flags() {
            std::cout << std::format("{:08b}\n|S|Z|x|H|y|P|N|C|\n|{}|{}| |{}| |{}|{}|{}|", 
                flags(), fch(sign()), fch(zero()), fch(half_carry()), fch(parity_overflow()), fch(negate()), fch(carry()));
        }

    private:

        inline int8_t& flags() {
            return sram[0];
        }

        inline char fch(bool f) {
            return f ? 'T' : 'F';
        }

        register_array_t sram;  // Z80 CPU's registers are implemented using static RAM.

    };


    static registers_t<Z80_REGISTER_COUNT> regs;


}