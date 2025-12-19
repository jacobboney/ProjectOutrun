#pragma once
#include <unordered_map>

#include "../defines.h"

// Forward declaration 
class Bus6502;

enum StatusFlags6502 { // Status Register (P) Bit positions
    CARRY = 0,
    ZERO,
    INTERRUPT_DISABLE,
    DECIMAL_MODE,
    BREAK_COMMAND,
    EXPANSION,
    V_OVERFLOW,
    N_NEGATIVE,
};

struct Registers6502 {
    Byte A;  // Accumulator
    Byte X;  // X Register
    Byte Y;  // Y Register
    Byte SP; // Stack Pointer
    Word PC; // Program Counter
    Byte P;  // Status Register

    Registers6502();

    void setFlag(StatusFlags6502 flag, bool state);
    bool getFlag(StatusFlags6502 flag);

    bool operator==(const Registers6502& registers) const;
};

class CPU6502 {

    public:
    CPU6502();
    ~CPU6502();
    void connectBus(Bus6502* busPtr);
    Bus6502* getBus();

    // Core Cpu Operations
    int  reset();
    int  clock();
    Byte read(Word address);
    int  write(Word address, Byte data);

    // Testing support functions
    Byte          getOpcode();
    Word          getAddress();
    Byte          getHigh();
    Byte          getLow();
    Byte          getZp();
    Byte          getData();
    int           getMicrostep();
    long          getCycles();   
    Registers6502 getRegisters();
    void          setRegisters(const Registers6502& registers);
    void          testReset();

    private:

    Bus6502* bus;            // System Bus Pointer
    Registers6502 registers; // CPU Registers

    Byte opcode;  // Current opcode being executed
    Word address; // Current address being accessed
    Byte high;    // High byte of the current instruction address
    Byte low;     // Low byte of the current instruction address
    Byte zp;      // Zero page address

    Byte data;    // Data being read/written

    int microstep; // Current microstep within instruction
    long  cycles;  // Total number of cycles executed

    std::unordered_map<Byte, void(CPU6502::*)()> instructions;

    // Instructions
    void brk_impl();     // $00 BRK - 2 Cycles - Break Command
    void ora_zp_ind_x(); // $01 ORA - 6 Cycles - ORA - "OR" Memory with Accumulator - X-Indexed Zero Page Indirect
    void ora_zp();       // $05 ORA - 3 Cycles - ORA - "OR" Memory with Accumulator - Zero Page
    void asl_zp();       // $06 ASL - 5 Cycles - ASL - Arithmetic Shift Left - Zero Page
};