#include "bus6502.h"

Bus6502::Bus6502()
{
    cpu.connectBus(this);
    memory.connectBus(this);
}

Bus6502::~Bus6502()
{
}

Byte Bus6502::memRead(Word address)
{
    return memory.read(address);
}

int Bus6502::memWrite(Word address, Byte data)
{
    return memory.write(address, data);
}

CPU6502 *Bus6502::getCPU()
{
    return &cpu;
}

Memory6502 *Bus6502::getMemory()
{
    return &memory;
}
