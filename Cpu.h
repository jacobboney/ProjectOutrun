//
// Created by jacob on 5/15/2023.
//

#pragma once
#include <cstdint>

using Byte = uint8_t;
using Word = uint16_t;

class Cpu {

    Byte a; // Accumulator Register
    Byte x; // X Register
    Byte y; // Y Register

    Byte s; // Stack Pointer
    Word pc; // Program Counter
    Byte p; // Processor Status | Ordering of flags are: N(7-Negative), V(6-Overflow), -(5-Expansion), B(4-Break Command), D(3-Decimal), I(2-Interrupt Disable), Z(1-Zero), C(0-Carry)

    // Address Modes
    Word ACC(); // Accumulator
    Word ABS(); // Absolute
    Word ABX(); // Absolute, X-Indexed
    Word ABY(); // Absolute, Y-Indexed
    Word IMM(); // Immediate
    Word IMP(); // Implied
    Word IND(); // Indirect
    Word INX(); // Indirect, X-Indexed
    Word INY(); // Indirect, Y-Indexed
    Word REL(); // Relative
    Word ZPG(); // Zero Page
    Word ZPX(); // Zero Page, X-Indexed
    Word ZPY(); // Zero Page, Y-Indexed

    //Opcodes
    //Add opcodes here and then declare in .cpp


public:

};

