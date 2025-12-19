#include "memory6502.h"
#include "../bus6502/bus6502.h"

Memory6502::Memory6502()
{
    ram.fill(0x00); // Initialize memory to 0x00
}

Memory6502::~Memory6502()
{
}

void Memory6502::connectBus(Bus6502 *busPtr)
{
    bus = busPtr;
}

Byte Memory6502::read(Word address)
{
    if(address >= 0x0000 && address <= 0xFFFF) { 
        return ram[address]; 
    }
    else { 
        return 0x00;
    }
}

int Memory6502::write(Word address, Byte data)
{
    if(address >= 0x0000 && address <= 0xFFFF) { 
        ram[address] = data; 
        return 0;
    }
    return 1;
}

void Memory6502::clear()
{
    ram.fill(0x00);
}
