#pragma once
#include "../defines.h"
#include "../cpu6502/cpu6502.h"
#include "../memory6502/memory6502.h"


class Bus6502 {

    public:
        Bus6502();
        ~Bus6502();

        Byte memRead (Word address);            // Read a byte from memory
        int  memWrite(Word address, Byte data); // Write a byte to memory

        // Pointers for testing purposes
        CPU6502*    getCPU();
        Memory6502* getMemory();

    private:
        CPU6502    cpu;    // CPU Instance
        Memory6502 memory; // Memory Instance

};