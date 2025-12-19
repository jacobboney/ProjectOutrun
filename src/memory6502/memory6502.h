#pragma once
#include "../defines.h"
#include <array>

// Forward declaration 
class Bus6502;

class Memory6502 {

    public: 
        Memory6502();
        ~Memory6502();
        void connectBus(Bus6502* busPtr);

        // Core Memory Operations
        Byte read (Word address);            // Read a byte from memory
        int  write(Word address, Byte data); // Write a byte to memory
        void clear();                        // Clear Memory (for testing)
    private: 

        Bus6502* bus;

        std::array<Byte, 64 * 1024> ram; // 64KB Memory
         
};