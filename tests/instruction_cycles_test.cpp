#include <gtest/gtest.h>
#include "../src/bus6502/bus6502.h"
#include "../src/cpu6502/cpu6502.h"

Bus6502 bus;
Registers6502 testRegisters;

// $00 BRK Instruction Tests
TEST(BRK_IMP, Setup) {
    // Stage CPU registers for BRK instruction test
    testRegisters = Registers6502();
    testRegisters.PC = 0x8000;
    testRegisters.SP = 0xFD;
    testRegisters.setFlag(INTERRUPT_DISABLE, true);
    bus.getCPU()->testReset(); 
    bus.getCPU()->setRegisters(testRegisters);

    // Stage Memory for BRK instruction test
    bus.getMemory()->clear();
    bus.memWrite(0x8000, 0x00); // BRK opcode
    bus.memWrite(0x8001, 0x42); // Next instruction (for PC increment)
    bus.memWrite(0xFFFE, 0x34); // Interrupt Vector Low Byte
    bus.memWrite(0xFFFF, 0x12); // Interrupt Vector High Byte

    // Confirm setup
    EXPECT_EQ(bus.getCPU()->getRegisters(), testRegisters);
    EXPECT_EQ(bus.memRead(0x8000), 0x00);
    EXPECT_EQ(bus.memRead(0x8001), 0x42);
    EXPECT_EQ(bus.memRead(0xFFFE), 0x34);
    EXPECT_EQ(bus.memRead(0xFFFF), 0x12);
}

TEST(BRK_IMP, Cycle_1) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 1);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 1);

    EXPECT_EQ(bus.getCPU()->getOpcode(), 0x00);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8001);
}

TEST(BRK_IMP, Cycle_2) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 2);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 2);

    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8002);
}

TEST(BRK_IMP, Cycle_3) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 3);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 3);

    EXPECT_EQ(bus.memRead(0x01FD), 0x80);
    EXPECT_EQ(bus.getCPU()->getRegisters().SP, 0xFC);
}

TEST(BRK_IMP, Cycle_4) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 4);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 4);

    EXPECT_EQ(bus.memRead(0x01FC), 0x02);
    EXPECT_EQ(bus.getCPU()->getRegisters().SP, 0xFB);
}

TEST(BRK_IMP, Cycle_5) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 5);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 5);

    Byte statusOnStack = 0x00 | (1 << BREAK_COMMAND) | (1 << EXPANSION) | (1 << INTERRUPT_DISABLE);

    EXPECT_EQ(bus.memRead(0x01FB), statusOnStack);
    EXPECT_EQ(bus.getCPU()->getRegisters().SP, 0xFA);
}

TEST(BRK_IMP, Cycle_6) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 6);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 6);

    EXPECT_EQ(bus.memRead(0xFFFE), 0x34);
}

TEST(BRK_IMP, Cycle_7) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 7);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 0);

    EXPECT_EQ(bus.memRead(0xFFFF), 0x12);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x1234);
    EXPECT_EQ(bus.getCPU()->getRegisters().SP, 0xFA);
    
}




// $01 ORA (Indirect,X) Instruction Tests
TEST(ORA_ZP_IND_X, Setup) {
    // Stage CPU registers for ORA (Indirect,X) instruction test
    testRegisters = Registers6502();
    testRegisters.PC = 0x8000;
    testRegisters.A = 0x10;
    testRegisters.X = 0x04;
    bus.getCPU()->testReset();
    bus.getCPU()->setRegisters(testRegisters);

    // Stage Memory for ORA (Indirect,X) instruction test
    bus.getMemory()->clear();
    bus.memWrite(0x8000, 0x01); // ORA (Indirect,X) opcode
    bus.memWrite(0x8001, 0x20); // Zero Page base address
    bus.memWrite(0x0024, 0x00); // Low byte of effective address
    bus.memWrite(0x0025, 0x90); // High byte of effective address
    bus.memWrite(0x9000, 0x0F); // Operand to OR with Accumulator

    // Confirm setup
    EXPECT_EQ(bus.getCPU()->getRegisters(), testRegisters);
    EXPECT_EQ(bus.memRead(0x8000), 0x01);
    EXPECT_EQ(bus.memRead(0x8001), 0x20);
    EXPECT_EQ(bus.memRead(0x0024), 0x00);
    EXPECT_EQ(bus.memRead(0x0025), 0x90);
    EXPECT_EQ(bus.memRead(0x9000), 0x0F);
}

TEST(ORA_ZP_IND_X, Cycle_1) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 1);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 1);

    EXPECT_EQ(bus.getCPU()->getOpcode(), 0x01);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8001);
}

TEST(ORA_ZP_IND_X, Cycle_2) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 2);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 2);

    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8002);

}

TEST(ORA_ZP_IND_X, Cycle_3) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 3);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 3);

    EXPECT_EQ(bus.getCPU()->getZp(), 0x24);
    EXPECT_EQ(bus.getCPU()->getLow(), 0x00);
}

TEST(ORA_ZP_IND_X, Cycle_4) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 4);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 4);

    EXPECT_EQ(bus.getCPU()->getZp(), 0x24);
    EXPECT_EQ(bus.getCPU()->getHigh(), 0x90);
    EXPECT_EQ(bus.getCPU()->getAddress(), 0x9000);
}

TEST(ORA_ZP_IND_X, Cycle_5) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 5);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 5);

    EXPECT_EQ(bus.getCPU()->getData(), 0x0F);
}

TEST(ORA_ZP_IND_X, Cycle_6) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 6);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 0);

    Byte statusOnStack = 0x00;

    EXPECT_EQ(bus.getCPU()->getRegisters().A, 0x1F);
    EXPECT_EQ(bus.getCPU()->getRegisters().P, statusOnStack);
}




// $05 ORA (Zero Page) Instruction Tests
TEST(ORA_ZP, Setup) {
    // Stage CPU registers for ORA (Zero Page) instruction test
    testRegisters = Registers6502();
    testRegisters.PC = 0x8000;
    testRegisters.A = 0x10;
    bus.getCPU()->testReset();
    bus.getCPU()->setRegisters(testRegisters);

    // Stage Memory for ORA (Zero Page) instruction test
    bus.getMemory()->clear();
    bus.memWrite(0x8000, 0x05); // ORA (Zero Page) opcode
    bus.memWrite(0x8001, 0x44); // Zero Page address
    bus.memWrite(0x0044, 0x0F); // Operand to OR with Accumulator

    // Confirm setup
    EXPECT_EQ(bus.getCPU()->getRegisters(), testRegisters);
    EXPECT_EQ(bus.memRead(0x8000), 0x05);
    EXPECT_EQ(bus.memRead(0x8001), 0x44);
    EXPECT_EQ(bus.memRead(0x0044), 0x0F);
}

TEST(ORA_ZP, Cycle_1) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 1);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 1);

    EXPECT_EQ(bus.getCPU()->getOpcode(), 0x05);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8001);
}

TEST(ORA_ZP, Cycle_2) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 2);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 2);

    EXPECT_EQ(bus.getCPU()->getZp(), 0x44);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8002);
    EXPECT_EQ(bus.getCPU()->getAddress(), 0x0044);
}

TEST(ORA_ZP, Cycle_3) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 3);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 0);

    Byte statusOnStack = 0x00;

    EXPECT_EQ(bus.getCPU()->getData(), 0x0F);
    EXPECT_EQ(bus.getCPU()->getRegisters().A, 0x1F);
    EXPECT_EQ(bus.getCPU()->getRegisters().P, statusOnStack);
}




// $06 ASL (Zero Page) Instruction Tests
TEST(ASL_ZP, Setup) {
    // Stage CPU registers for ORA (Zero Page) instruction test
    testRegisters = Registers6502();
    testRegisters.PC = 0x8000;
    bus.getCPU()->testReset();
    bus.getCPU()->setRegisters(testRegisters);

    // Stage Memory for ORA (Zero Page) instruction test
    bus.getMemory()->clear();
    bus.memWrite(0x8000, 0x06); // ORA (Zero Page) opcode
    bus.memWrite(0x8001, 0x10); // Zero Page address
    bus.memWrite(0x0010, 0x80); // Operand to OR with Accumulator

    // Confirm setup
    EXPECT_EQ(bus.getCPU()->getRegisters(), testRegisters);
    EXPECT_EQ(bus.memRead(0x8000), 0x06);
    EXPECT_EQ(bus.memRead(0x8001), 0x10);
    EXPECT_EQ(bus.memRead(0x0010), 0x80);
}

TEST(ASL_ZP, Cycle_1) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 1);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 1);

    EXPECT_EQ(bus.getCPU()->getOpcode(), 0x06);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8001);
}

TEST(ASL_ZP, Cycle_2) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 2);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 2);

    EXPECT_EQ(bus.getCPU()->getZp(), 0x10);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8002);
    EXPECT_EQ(bus.getCPU()->getAddress(), 0x0010);
}

TEST(ASL_ZP, Cycle_3) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 3);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 3);

    EXPECT_EQ(bus.getCPU()->getData(), 0x80);
}

TEST(ASL_ZP, Cycle_4) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 4);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 4);

    EXPECT_EQ(bus.getCPU()->getData(), 0x80);
    EXPECT_EQ(bus.memRead(0x0010), 0x80);
}

TEST(ASL_ZP, Cycle_5) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 5);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 0);

    Byte statusOnStack = 0x00 | (1 << CARRY) | (1 << ZERO);

    EXPECT_EQ(bus.memRead(0x0010), 0x00);
    EXPECT_EQ(bus.getCPU()->getRegisters().P, statusOnStack);
}




// $08 PHP Instruction Tests
TEST(PHP_IMPL, Setup) {
    // Stage CPU registers for PHP instruction test
    testRegisters = Registers6502();
    testRegisters.PC = 0x8000;
    testRegisters.SP = 0xFD;
    testRegisters.P = 0x24;
    bus.getCPU()->testReset();
    bus.getCPU()->setRegisters(testRegisters);

    // Stage memory for PHP instruction test
    bus.getMemory()->clear();
    bus.memWrite(0x8000, 0x08); // PHP opcode

    // Confirm setup
    EXPECT_EQ(bus.getCPU()->getRegisters(), testRegisters);
    EXPECT_EQ(bus.memRead(0x8000), 0x08);
}

TEST(PHP_IMPL, Cycle_1) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 1);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 1);

    EXPECT_EQ(bus.getCPU()->getOpcode(), 0x08);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8001);
}

TEST(PHP_IMPL, Cycle_2) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 2);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 2);

    Byte statusOnStack = 0x24;
    Byte data = statusOnStack | (1 << BREAK_COMMAND) | (1 << EXPANSION);

    EXPECT_EQ(bus.getCPU()->getRegisters().P, statusOnStack);
    EXPECT_EQ(bus.getCPU()->getData(), data);
    EXPECT_EQ(bus.getCPU()->getAddress(), 0x01FD);
}

TEST(PHP_IMPL, Cycle_3) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 3);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 0);

    Byte statusOnStack = 0x24;
    Byte data = statusOnStack | (1 << BREAK_COMMAND) | (1 << EXPANSION);

    EXPECT_EQ(bus.getCPU()->getRegisters().P, statusOnStack);
    EXPECT_EQ(bus.memRead(0x01FD), data);
    EXPECT_EQ(bus.getCPU()->getRegisters().SP, 0xFC);
}




// $09 ORA (Immediate) Instruction Tests
TEST(ORA_IMM, Setup) {
    // Stage CPU registers for PHP instruction test
    testRegisters = Registers6502();
    testRegisters.PC = 0x8000;
    testRegisters.A = 0x10;
    bus.getCPU()->testReset();
    bus.getCPU()->setRegisters(testRegisters);

    // Stage memory for PHP instruction test
    bus.getMemory()->clear();
    bus.memWrite(0x8000, 0x09); // ORA (Immediate) opcode
    bus.memWrite(0x8001, 0x0F); // Operand to OR with Accumulator

    // Confirm setup
    EXPECT_EQ(bus.getCPU()->getRegisters(), testRegisters);
    EXPECT_EQ(bus.memRead(0x8000), 0x09);
    EXPECT_EQ(bus.memRead(0x8001), 0x0F);
}

TEST(ORA_IMM, Cycle_1) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 1);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 1);

    EXPECT_EQ(bus.getCPU()->getOpcode(), 0x09);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8001);
}

TEST(ORA_IMM, Cycle_2) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 2);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 0);

    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8002);
    EXPECT_EQ(bus.getCPU()->getData(), 0x0F);
    EXPECT_EQ(bus.getCPU()->getRegisters().A, 0x1F);
    EXPECT_EQ(bus.getCPU()->getRegisters().P, 0x00);
}




// $0A ASL (Accumulator) Instruction Tests
TEST(ASL_ACC, Setup) {
    // Stage CPU registers for ASL (Accumulator) instruction test
    testRegisters = Registers6502();
    testRegisters.PC = 0x8000;
    testRegisters.A = 0x81;
    bus.getCPU()->testReset();
    bus.getCPU()->setRegisters(testRegisters);

    // Stage memory for ASL (Accumulator) instruction test
    bus.getMemory()->clear();
    bus.memWrite(0x8000, 0x0A); // ASL (Accumulator) opcode

    // Confirm setup
    EXPECT_EQ(bus.getCPU()->getRegisters(), testRegisters);
    EXPECT_EQ(bus.memRead(0x8000), 0x0A);
}

TEST(ASL_ACC, Cycle_1) {
    bus.getCPU()->clock();
    
    EXPECT_EQ(bus.getCPU()->getCycles()   , 1);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 1);

    EXPECT_EQ(bus.getCPU()->getOpcode(), 0x0A);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8001);
}

TEST(ASL_ACC, Cycle_2) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 2);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 0);

    Byte statusOnStack = 0x00 | (1 << CARRY);

    EXPECT_EQ(bus.getCPU()->getRegisters().A, 0x02);
    EXPECT_EQ(bus.getCPU()->getRegisters().P, statusOnStack);
}




// $0D ORA (Absolute) Instruction Tests
TEST(ORA_ABS, Setup) {
    // Stage CPU registers for ORA (Absolute) instruction test
    testRegisters = Registers6502();
    testRegisters.PC = 0x8000;
    testRegisters.A  = 0x10;
    bus.getCPU()->testReset();
    bus.getCPU()->setRegisters(testRegisters);

    // Stage memory for ORA (Absolute) instruction test
    bus.getMemory()->clear();
    bus.memWrite(0x8000, 0x0D); // ORA abs opcode
    bus.memWrite(0x8001, 0x34); // low byte of address
    bus.memWrite(0x8002, 0x12); // high byte of address
    bus.memWrite(0x1234, 0x0F); // operand

    // Confirm setup
    EXPECT_EQ(bus.getCPU()->getRegisters(), testRegisters);
    EXPECT_EQ(bus.memRead(0x8000), 0x0D);
    EXPECT_EQ(bus.memRead(0x8001), 0x34);
    EXPECT_EQ(bus.memRead(0x8002), 0x12);
    EXPECT_EQ(bus.memRead(0x1234), 0x0F);
}

TEST(ORA_ABS, Cycle_1) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 1);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 1);

    EXPECT_EQ(bus.getCPU()->getOpcode(), 0x0D);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8001);
}

TEST(ORA_ABS, Cycle_2) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 2);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 2);

    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8002);
    EXPECT_EQ(bus.getCPU()->getLow(), 0x34);
}

TEST(ORA_ABS, Cycle_3) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 3);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 3);

    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8003);
    EXPECT_EQ(bus.getCPU()->getHigh(), 0x12);
    EXPECT_EQ(bus.getCPU()->getAddress(), 0x1234);
}

TEST(ORA_ABS, Cycle_4) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 4);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 0);

    Byte statusOnStack = 0x00;

    EXPECT_EQ(bus.getCPU()->getRegisters().A, 0x1F);
    EXPECT_EQ(bus.getCPU()->getRegisters().P, statusOnStack);
}




// $0E ASL (Absolute) Instruction Tests
TEST(ASL_ABS, Setup) {
    // Stage CPU registers for ASL (Absolute) instruction test
    testRegisters = Registers6502();
    testRegisters.PC = 0x8000;
    testRegisters.A  = 0x10;
    bus.getCPU()->testReset();
    bus.getCPU()->setRegisters(testRegisters);

    // Stage memory for ASL (Absolute) instruction test
    bus.getMemory()->clear();
    bus.memWrite(0x8000, 0x0E); // ASL abs opcode
    bus.memWrite(0x8001, 0x34); // low byte of address
    bus.memWrite(0x8002, 0x12); // high byte of address
    bus.memWrite(0x1234, 0x0F); // operand

    // Confirm setup
    EXPECT_EQ(bus.getCPU()->getRegisters(), testRegisters);
    EXPECT_EQ(bus.memRead(0x8000), 0x0E);
    EXPECT_EQ(bus.memRead(0x8001), 0x34);
    EXPECT_EQ(bus.memRead(0x8002), 0x12);
    EXPECT_EQ(bus.memRead(0x1234), 0x0F);
}

TEST(ASL_ABS, Cycle_1) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 1);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 1);

    EXPECT_EQ(bus.getCPU()->getOpcode(), 0x0E);
    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8001);
}

TEST(ASL_ABS, Cycle_2) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 2);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 2);

    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8002);
    EXPECT_EQ(bus.getCPU()->getLow(), 0x34);
}

TEST(ASL_ABS, Cycle_3) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 3);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 3);

    EXPECT_EQ(bus.getCPU()->getRegisters().PC, 0x8003);
    EXPECT_EQ(bus.getCPU()->getHigh(), 0x12);
    EXPECT_EQ(bus.getCPU()->getAddress(), 0x1234);
}

TEST(ASL_ABS, Cycle_4) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 4);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 4);

    EXPECT_EQ(bus.getCPU()->getData(), 0x0F);
}

TEST(ASL_ABS, Cycle_5) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 5);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 5);

    Byte statusOnStack = 0x00;

    EXPECT_EQ(bus.getCPU()->getData(), 0x1E);
    EXPECT_EQ(bus.getCPU()->getRegisters().P, statusOnStack);
}

TEST(ASL_ABS, Cycle_6) {
    bus.getCPU()->clock();

    EXPECT_EQ(bus.getCPU()->getCycles()   , 6);
    EXPECT_EQ(bus.getCPU()->getMicrostep(), 0);

    EXPECT_EQ(bus.memRead(0x1234), 0x1E);
}
