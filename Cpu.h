//
// Created by jacob on 5/15/2023.
//

#pragma once
#include <cstdint>
#include <string>

using Byte = uint8_t;
using Word = uint16_t;

class Cpu {

private:
    Byte a; // Accumulator Register
    Byte x; // X Register
    Byte y; // Y Register

    Byte s; // Stack Pointer
    Word pc; // Program Counter
    Byte p; // Processor Status | Ordering of flags are: N(7-Negative), V(6-Overflow), -(5-Expansion), B(4-Break Command), D(3-Decimal), I(2-Interrupt Disable), Z(1-Zero), C(0-Carry)


    struct Instructions { // This struct handles the creation of the instruction set made up of both the opcode and the addressing mode
        std::string name;
        Byte Cpu::*addressMode = nullptr;
        Byte Cpu::*opcode = nullptr;
        Byte cycles = 0;
    };

    Instructions lookupTable[256];

    // Address Modes
    Byte ACC(); // Accumulator
    Byte ABS(); // Absolute
    Byte ABX(); // Absolute, X-Indexed
    Byte ABY(); // Absolute, Y-Indexed
    Byte IMM(); // Immediate
    Byte IMP(); // Implied
    Byte IND(); // Indirect
    Byte IDX(); // Indirect, X-Indexed
    Byte IDY(); // Indirect, Y-Indexed
    Byte REL(); // Relative
    Byte ZPG(); // Zero Page
    Byte ZPX(); // Zero Page, X-Indexed
    Byte ZPY(); // Zero Page, Y-Indexed

    //Opcodes
    //Add opcodes here and then declare in .cpp
    Byte ADC(); // Add with carry
    Byte AND(); // And (with accumulator)
    Byte ASL(); // Arithmetic Shift Left
    Byte BCC(); // Branch on carry clear
    Byte BCS(); // Branch on carry set
    Byte BEQ(); // Branch on equal (zero set)
    Byte BIT(); // Bit test
    Byte BMI(); // Branch on minus (negative set)
    Byte BNE(); // Branch on not equal (zero clear)
    Byte BPL(); // Branch on plus (negative clear)
    Byte BRK(); // Break / interrupt
    Byte BVC(); // Branch on overflow clear
    Byte BVS(); // Branch on overflow set
    Byte CLC(); // Clear Carry
    Byte CLD(); // Clear Decimal
    Byte CLI(); // Clear interrupt disable
    Byte CLV(); // Clear overflow
    Byte CMP(); // Compare (with accumulator)
    Byte CPX(); // Compare with X
    Byte CPY(); // Compare with Y
    Byte DEC(); // Decrement
    Byte DEX(); // Decrement X
    Byte DEY(); // Decrement Y
    Byte EOR(); // Exclusive or (with accumulator)
    Byte INC(); // Increment
    Byte INX(); // Increment X
    Byte INY(); // Increment Y
    Byte JMP(); // Jump
    Byte JSR(); // Jump Subroutine
    Byte LDA(); // Load accumulator
    Byte LDX(); // Load X
    Byte LDY(); // Load Y
    Byte LSR(); // Logical shift right
    Byte NOP(); // No operation
    Byte ORA(); // Or with accumulator
    Byte PHA(); // Push accumulator
    Byte PHP(); // Push processor status (SR)
    Byte PLA(); // Pull accumulator
    Byte PLP(); // Pull processor status (SR)
    Byte ROL(); // Rotate left
    Byte ROR(); // Rotate right
    Byte RTI(); // Return from interrupt
    Byte RTS(); // Return from subroutine
    Byte SBC(); // Subtract with cary
    Byte SEC(); // Set carry
    Byte SED(); // Set decimal
    Byte SEI(); // Set interrupt disable
    Byte STA(); // Store accumulator
    Byte STX(); // Store X
    Byte STY(); // Store Y
    Byte TAX(); // Transfer accumulator to X
    Byte TAY(); // Transfer accumulator to Y
    Byte TSX(); // Transfer stack pointer to X
    Byte TXA(); // Transfer X to accumulator
    Byte TXS(); // Transfer X to stack pointer
    Byte TYA(); // Transfer Y to accumulator

};































