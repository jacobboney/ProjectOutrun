#include "cpu6502.h"
#include "../bus6502/bus6502.h"

CPU6502::CPU6502()
{
    // On power on the reset pin is held low to trigger a reset to place the cpu in a known state
    // Will revisit for pin simulation later
    cycles = 0;
    microstep = 0;
    reset();

    // Initialize Instruction Set
    instructions[0x00] = &CPU6502::brk_impl;
    instructions[0x01] = &CPU6502::ora_zp_ind_x;
    instructions[0x02] = nullptr;
    instructions[0x03] = nullptr;
    instructions[0x04] = nullptr;
    instructions[0x05] = &CPU6502::ora_zp;
    instructions[0x06] = &CPU6502::asl_zp;
    instructions[0x07] = nullptr;
    instructions[0x08] = &CPU6502::php_impl;
    instructions[0x09] = &CPU6502::ora_imm;
    instructions[0x0A] = &CPU6502::asl_acc;
    instructions[0x0B] = nullptr;
    instructions[0x0C] = nullptr;
    instructions[0x0D] = &CPU6502::ora_abs;
    instructions[0x0E] = &CPU6502::asl_abs;
    instructions[0x0F] = nullptr;
    instructions[0x10] = &CPU6502::bpl_rel;
}

CPU6502::~CPU6502()
{
}

void CPU6502::connectBus(Bus6502 *busPtr)
{
    bus = busPtr;
}

Bus6502 *CPU6502::getBus()
{
    return bus;
}

int CPU6502::reset()
{
    switch(microstep) {
        case 0: {
            // Dummy Cycle
            microstep++;
            cycles++;
            break;
        }
        case 1: {
            //Dummy Cycle
            microstep++;
            cycles++;
            break;
        }
        case 2: {
            // Fetch Low Byte of Reset Vector
            address = 0xFFFC;
            low = read(address);

            microstep++;
            cycles++;
            break;
        }
        case 3: {
            // Fetch High Byte of Reset Vector
            address = 0xFFFD;
            high = read(address);

            microstep++;
            cycles++;
            break;
        }
        case 4: {
            // Set Program Counter to Address from Reset Vector
            registers.PC = (high << 8) | low;

            // Set Interrupt Disable Flag
            registers.setFlag(INTERRUPT_DISABLE, true);

            microstep++;
            cycles++;
            break;
        }
        case 5: {
            // Internal Operations (Maybe need to revisit  for pin simulation)
            microstep++;
            cycles++;
            break;
        }
        case 6: {
            // Fetch Opcode at Reset Vector Address
            opcode = read(registers.PC);
            registers.PC++;

            // Reset complete, set microstep to 1 for normal operation
            microstep = 1; 
            cycles++;
            break;
        }
    }

    return 0;
}

int CPU6502::clock()
{
    if(microstep == 0) {
        //Fetch opcode
        opcode = read(registers.PC);
        registers.PC++;
        microstep++;
        cycles++;
    }
    else {
        // Execute instruction micro-operations
        (this->*instructions[opcode])();
    }


    return 0;
}

Byte CPU6502::read(Word address)
{
    // Revisit for pin simulation
    return bus->memRead(address); // Read a byte from memory
}

int CPU6502::write(Word address, Byte data)
{
    // Revisit for pin simulation
    return bus->memWrite(address, data); // Write a byte to memory
}

Byte CPU6502::getOpcode()
{
    return opcode;
}

Word CPU6502::getAddress()
{
    return address;
}

Byte CPU6502::getHigh()
{
    return high;
}

Byte CPU6502::getLow()
{
    return low;
}

Byte CPU6502::getZp()
{
    return zp;
}

Byte CPU6502::getData()
{
    return data;
}

int CPU6502::getMicrostep()
{
    return microstep;
}

long CPU6502::getCycles()
{
    return cycles;
}

Registers6502 CPU6502::getRegisters()
{
    return registers;
}

void CPU6502::setRegisters(const Registers6502 &registers)
{
    this->registers = registers;
}

void CPU6502::testReset()
{
    microstep = 0;
    cycles = 0;
    registers = Registers6502();
}

Registers6502::Registers6502()
{
    A  = 0x00;
    X  = 0x00;
    Y  = 0x00;
    SP = 0x00;
    PC = 0x0000;
    P  = 0x00; 
}

void Registers6502::setFlag(StatusFlags6502 flag, bool state)
{
    if(state) { P |=  (1 << flag); } // If true, set the flag
    else      { P &= ~(1 << flag); } // If false, clear the flag
}

bool Registers6502::getFlag(StatusFlags6502 flag)
{
    return (P & (1 << flag)) != 0; // Get input flag state
}

bool Registers6502::operator==(const Registers6502 &registers) const
{
    return (A  == registers.A  &&
            X  == registers.X  &&
            Y  == registers.Y  &&
            SP == registers.SP &&
            PC == registers.PC &&
            P  == registers.P);
}
