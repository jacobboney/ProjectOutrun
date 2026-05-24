#include "cpu6502.h"

/* Instruction definitions reside within this file. Instructions are loaded by hex value into the instructions map contained
    within thje 6502 class. The clock() function handles the "first" micro instruction as it is simply fetching the opcode and
    incrementing the PC which should be the same for all instructions.
*/ 

// $00 BRK
void CPU6502::brk_impl()
{
    switch(microstep) {
        case 1: {
            // Dummy Read
            read(registers.PC);
            registers.PC++;
            microstep++;
            cycles++;

            break;
        }
        case 2: {
            // Push High Byte of PC to Stack
            address = 0x0100 + registers.SP;
            high = (registers.PC >> 8) & 0x00FF;
            write(address, high);
            registers.SP--;
            microstep++;
            cycles++;

            break;
        }
        case 3: {
            // Push Low Byte of PC to Stack
            address = 0x0100 + registers.SP;
            low = registers.PC & 0x00FF;
            write(address, low);
            registers.SP--;
            microstep++;
            cycles++;

            break;
        }
        case 4: {
            // Push Status Register to Stack
            address = 0x0100 + registers.SP;
            Byte virtualP = registers.P | (1 << BREAK_COMMAND) | (1 << EXPANSION);
            write(address, virtualP);
            registers.SP--;
            registers.setFlag(INTERRUPT_DISABLE, true);
            microstep++;
            cycles++;

            break;
        }
        case 5: {
            // Fetch Low Byte of Interrupt Vector
            address = 0xFFFE;
            low = read(address);
            microstep++;
            cycles++;
    
            break;
        }
        case 6: {
            // Fetch High Byte of Interrupt Vector
            address = 0xFFFF;
            high = read(address);

            // Set Program Counter to Interrupt Vector Address
            registers.PC = (high << 8) | low;

            // Reset microstep for next instruction
            microstep = 0; 
            cycles++;

            break;
        }
        default: {
            return;
        }
    }
}




// $01 ORA
void CPU6502::ora_zp_ind_x()
{
    switch(microstep) {
        case 1: {
            // Fetch Zero Page Pointer Base
            data = read(registers.PC);
            registers.PC++;
            microstep++;
            cycles++;

            break; 
        }
        case 2: {
            // Read Low Byte of Effective Address
            zp = (data + registers.X) & 0xFF;
            low = read(zp);
            microstep++;
            cycles++;

            break;
        }
        case 3: {
            // Read High Byte of Effective Address
            high = read((zp + 1) & 0xFF);
            address = (high << 8) | low;
            microstep++;
            cycles++;
        
            break;
        }
        case 4: {
            // Read Operand from Effective Address
            data = read(address);
            microstep++;
            cycles++;

            break;
        }
        case 5: {
            // ORA Operation
            registers.A |= data;
            registers.setFlag(ZERO, registers.A == 0);
            registers.setFlag(N_NEGATIVE, (registers.A & 0x80) != 0);
            microstep = 0;
            cycles++;

            break;
        }
        default: {
            return;
        }
    }
}




// $05 ORA
void CPU6502::ora_zp()
{
    switch(microstep) {
        case 1: {
            // Fetch Zero Page Address
            zp = read(registers.PC);
            registers.PC++;
            address = zp & 0x00FF;
            microstep++;
            cycles++;

            break;
        }
        case 2: {
            // ORA Operation
            data = read(address);
            registers.A |= data;
            registers.setFlag(ZERO, registers.A == 0);
            registers.setFlag(N_NEGATIVE, (registers.A & 0x80) != 0);
            microstep = 0;
            cycles++;

            break;
        }
        default: {
            return;
        }
    }
}




// $06 ASL
void CPU6502::asl_zp()
{
    switch(microstep) {
        case 1: {
            // Fetch Zero Page Address
            zp = read(registers.PC);
            registers.PC++;
            address = zp & 0x00FF;
            microstep++;
            cycles++;

            break; 
        }
        case 2: {
            // Read Value from Zero Page Address
            data = read(address);
            microstep++;
            cycles++;

            break;
        }
        case 3: {
            // Dummy Write (for timing)
            write(address, data);
            microstep++;
            cycles++;

            break;
        }
        case 4: {
            registers.setFlag(CARRY, (data & 0x80) != 0);
            data <<=1;
            write(address, data);
            registers.setFlag(N_NEGATIVE, (data & 0x80) != 0);
            registers.setFlag(ZERO, data == 0);
            microstep = 0;
            cycles++;

            break;
        }
        default: {
            return;
        }
    }
}




// $08 PHP
void CPU6502::php_impl()
{
    switch(microstep) {
        case 1: {
            // Stuff temp status register with B and unused bits set
            data = registers.P | (1 << BREAK_COMMAND) | (1 << EXPANSION);
            address = 0x0100 + registers.SP;
            microstep++;
            cycles++;

            break;
        }
        case 2: {
            // Push Status Register to Stack
            write(address, data);
            registers.SP--;
            microstep = 0;
            cycles++;

            break;
        }
        default: {
            return;
        }
    }
}




// $09 ORA
void CPU6502::ora_imm()
{
    switch(microstep) {
        case 1: {
            // ORA Operation
            data = read(registers.PC);
            registers.PC++;
            registers.A |= data;
            registers.setFlag(ZERO, registers.A == 0);
            registers.setFlag(N_NEGATIVE, (registers.A & 0x80) != 0);
            microstep = 0;
            cycles++;

            break;
        }
        default: {
            return;
        }
    }
}




// $0A ASL
void CPU6502::asl_acc()
{
    switch(microstep) {
        case 1: {
            // Left shift accumulator
            registers.setFlag(CARRY, (registers.A & 0x80) != 0);
            registers.A <<=1;
            registers.setFlag(N_NEGATIVE, (registers.A & 0x80) != 0);
            registers.setFlag(ZERO, registers.A == 0);
            microstep = 0;
            cycles++;

            break;
        }
        default: {
            return;
        }
    }
}




// $0D ORA
void CPU6502::ora_abs()
{
    switch(microstep) {
        case 1: {
            // Fetch Low Byte of Absolute Address
            low = read(registers.PC);
            registers.PC++;
            microstep++;
            cycles++;

            break;
        }
        case 2: {
            // Fetch High Byte of Absolute Address
            high = read(registers.PC);
            registers.PC++;
            address = (high << 8) | low;
            microstep++;
            cycles++;

            break;
        }
        case 3: {
            // ORA Operation
            data = read(address);
            registers.A |= data;
            registers.setFlag(ZERO, registers.A == 0);
            registers.setFlag(N_NEGATIVE, (registers.A & 0x80) != 0);
            microstep = 0;
            cycles++;
            
            break;
        }
        default: {
            return;
        }
    }
}




// $0E ASL
void CPU6502::asl_abs() 
{
    switch(microstep) {
        case 1: {
            low = read(registers.PC);
            registers.PC++;
            microstep++;
            cycles++;
            
            break;
        }
        case 2: {
            high = read(registers.PC);
            registers.PC++;
            address = (high << 8) | low; 
            microstep++;
            cycles++;

            break;
        }
        case 3: {
            data = read(address);
            microstep++;
            cycles++;

            break;
        }
        case 4: {
            write(address, data);
            registers.setFlag(CARRY, (data & 0x80) != 0);
            data <<= 1;
            registers.setFlag(N_NEGATIVE, (data & 0x80) != 0);
            registers.setFlag(ZERO, data == 0);
            microstep++;
            cycles++;

            break;
        }
        case 5: {
            write(address, data);
            microstep = 0;
            cycles++;

            break;
        }
        default: {
            return;
        }
    };
}




// $10 BPL
void CPU6502::bpl_rel() {
    
};
