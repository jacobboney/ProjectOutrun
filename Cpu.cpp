//
// Created by jacob on 5/15/2023.
//

#include "Cpu.h"
#include "Bus.h"

// Constructor
Cpu::Cpu() {

    // Initialize lookupTable with instruction set

    // Row 0
    lookupTable[0] = {"BRK", &Cpu::BRK, &Cpu::IMP, 7}; // BRK - Break Command | Implied | Opcode: $00
    lookupTable[1] = {"ORA", &Cpu::ORA, &Cpu::IDX, 6}; // ORA - "OR" Memory with Accumulator | X-Indexed Zero Page Indirect | Opcode: $01
    lookupTable[2] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[3] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[4] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[5] = {"ORA", &Cpu::ORA, &Cpu::ZPG, 3}; // ORA - "OR" Memory with Accumulator | Zero Page | Opcode: $05
    lookupTable[6] = {"ASL", &Cpu::ASL, &Cpu::ZPG, 5}; // ASL - Arithmetic Shift Left | Zero Page | Opcode: $06
    lookupTable[7] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[8] = {"PHP", &Cpu::PHP, &Cpu::IMP, 3}; // PHP - Push Processor Status On Stack | Implied | Opcode: $08
    lookupTable[9] = {"ORA", &Cpu::ORA, &Cpu::IMM, 2}; // ORA - "OR" Memory with Accumulator | Immediate | Opcode: $09
    lookupTable[10] = {"ASL", &Cpu::ASL, &Cpu::ACC, 2}; // ASL - Arithmetic Shift Left | Accumulator | Opcode: $0A
    lookupTable[11] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[12] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[13] = {"ORA", &Cpu::ORA, &Cpu::ABS, 4}; // ORA - "OR" Memory with Accumulator | Absolute | Opcode: $0D
    lookupTable[14] = {"ASL", &Cpu::ASL, &Cpu::ABS, 6}; // ASL - Arithmetic Shift Left | Absolute | Opcode: $0E
    lookupTable[15] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 1
    lookupTable[16] = {"BPL", &Cpu::BPL, &Cpu::REL, 2}; // BPL - Branch on Result Plus | Relative | Opcode: $10
    lookupTable[17] = {"ORA", &Cpu::ORA, &Cpu::ZPY, 4}; // ORA - "OR" Memory with Accumulator | Zero Page Indirect Y-Indexed | Opcode: $11
    lookupTable[18] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[19] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[20] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[21] = {"ORA", &Cpu::ORA, &Cpu::ZPX, 4}; // ORA - "OR" Memory with Accumulator | X-Indexed Zero Page | Opcode: $15
    lookupTable[22] = {"ASL", &Cpu::ASL, &Cpu::ZPX, 6}; // ASL - Arithmetic Shift Left | X-Indexed Zero Page | Opcode: $16
    lookupTable[23] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[24] = {"CLC", &Cpu::CLC, &Cpu::IMP, 2}; // CLC - Clear Carry Flag | Implied | Opcode: $18
    lookupTable[25] = {"ORA", &Cpu::ORA, &Cpu::ABY, 4}; // ORA - "OR" Memory with Accumulator | Y-Indexed Absolute | Opcode: $19
    lookupTable[26] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[27] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[28] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[29] = {"ORA", &Cpu::ORA, &Cpu::ABX, 4}; // ORA - "OR" Memory with Accumulator | X-Indexed Absolute | Opcode: $1D
    lookupTable[30] = {"ASL", &Cpu::ASL, &Cpu::ABX, 7}; // ASL - Arithmetic Shift Left | X-Indexed Absolute | Opcode: $1E
    lookupTable[31] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial


    // Row 2
    lookupTable[32] = {"JSR", &Cpu::JSR, &Cpu::ABS, 6}; // JSR - Jump To Subroutine | Absolute | Opcode: $20
    lookupTable[33] = {"AND", &Cpu::AND, &Cpu::IDX, 6}; // AND - "AND" Memory with Accumulator | X-Indexed Zero Page Indirect | Opcode: $21
    lookupTable[34] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[35] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[36] = {"BIT", &Cpu::BIT, &Cpu::ZPG, 3}; // BIT - Test Bits in Memory with Accumulator | Zero Page | Opcode: $24
    lookupTable[37] = {"AND", &Cpu::AND, &Cpu::ZPG, 3}; // AND - "AND" Memory with Accumulator | Zero Page | Opcode: $25
    lookupTable[38] = {"ROL", &Cpu::ROL, &Cpu::ZPG, 5}; // ROL - Rotate Left | Zero Page | Opcode: $26
    lookupTable[39] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[40] = {"PLP", &Cpu::PLP, &Cpu::IMP, 4}; // PLP - Pull Processor Status From Stack | Implied | Opcode: $28
    lookupTable[41] = {"AND", &Cpu::AND, &Cpu::IMM, 2}; // AND - "AND" Memory with Accumulator | Immediate | Opcode: $29
    lookupTable[42] = {"ROL", &Cpu::ROL, &Cpu::ACC, 2}; // ROL - Rotate Left | Accumulator | Opcode: $2A
    lookupTable[43] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[44] = {"BIT", &Cpu::BIT, &Cpu::ABS, 4}; // BIT - Test Bits in Memory with Accumulator | Absolute | Opcode: $2C
    lookupTable[45] = {"AND", &Cpu::AND, &Cpu::ABS, 4}; // AND - "AND" Memory with Accumulator | Absolute | Opcode: $2D
    lookupTable[46] = {"ROL", &Cpu::ROL, &Cpu::ABS, 6}; // ROL - Rotate Left | Absolute | Opcode: $2E
    lookupTable[47] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 3
    lookupTable[48] = {"BMI", &Cpu::BMI, &Cpu::REL, 2}; // BMI - Branch on Result Minus | Relative | Opcode: $30
    lookupTable[49] = {"AND", &Cpu::AND, &Cpu::IDY, 5}; // AND - "AND" Memory with Accumulator | Zero Page Indirect Y-Indexed | Opcode: $31
    lookupTable[50] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[51] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[52] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[53] = {"AND", &Cpu::AND, &Cpu::ZPX, 4}; // AND - "AND" Memory with Accumulator | Zero Page Indirect Y-Indexed | Opcode: $35
    lookupTable[54] = {"ROL", &Cpu::ROL, &Cpu::ZPX, 6}; // ROL - Rotate Left | X-Indexed Zero Page | Opcode: $36
    lookupTable[55] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[56] = {"SEC", &Cpu::SEC, &Cpu::IMP, 2}; // SEC - Set Carry Flag | Implied | Opcode: $38
    lookupTable[57] = {"AND", &Cpu::AND, &Cpu::ABY, 4}; // AND - "AND" Memory with Accumulator | Y-Indexed Absolute | Opcode: $39
    lookupTable[58] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[59] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[60] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[61] = {"AND", &Cpu::AND, &Cpu::ABX, 4}; // AND - "AND" Memory with Accumulator | X-Indexed Absolute | Opcode: $3D
    lookupTable[62] = {"ROL", &Cpu::ROL, &Cpu::ABX, 7}; // ROL - Rotate Left | X-Indexed Absolute | Opcode: $3E
    lookupTable[63] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 4
    lookupTable[64] = {"RTI", &Cpu::RTI, &Cpu::IMP, 6}; // RTI - Return From Interrupt | Implied | Opcode: $40
    lookupTable[65] = {"EOR", &Cpu::EOR, &Cpu::IDX, 6}; // EOR - "Exclusive OR" Memory with Accumulator | X-Indexed Zero Page Indirect | Opcode: $41
    lookupTable[66] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[67] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[68] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[69] = {"EOR", &Cpu::EOR, &Cpu::ZPG, 3}; // EOR - "Exclusive OR" Memory with Accumulator | Zero Page | Opcode: $45
    lookupTable[70] = {"LSR", &Cpu::LSR, &Cpu::ZPG, 5}; // LSR - Logical Shift Right | Zero Page | Opcode: $46
    lookupTable[71] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[72] = {"PHA", &Cpu::PHA, &Cpu::IMP, 3}; // PHA - Push Accumulator On Stack | Implied | Opcode: $48
    lookupTable[73] = {"EOR", &Cpu::EOR, &Cpu::IMM, 2}; // EOR - "Exclusive OR" Memory with Accumulator | Immediate | Opcode: $49
    lookupTable[74] = {"LSR", &Cpu::LSR, &Cpu::ACC, 2}; // LSR - Logical Shift Right | Accumulator | Opcode: $4A
    lookupTable[75] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[76] = {"JMP", &Cpu::JMP, &Cpu::ABS, 3}; // JMP - JMP Indirect | Absolute | Opcode: $4C
    lookupTable[77] = {"EOR", &Cpu::EOR, &Cpu::ABS, 4}; // EOR - "Exclusive OR" Memory with Accumulator | Absolute | Opcode: $4D
    lookupTable[78] = {"LSR", &Cpu::LSR, &Cpu::ABS, 6}; // LSR - Logical Shift Right | Absolute | Opcode: $4E
    lookupTable[79] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 5
    lookupTable[80] = {"BVC", &Cpu::BVC, &Cpu::REL, 2}; // BVC - Branch on Overflow Clear | Relative | Opcode: $50
    lookupTable[81] = {"EOR", &Cpu::EOR, &Cpu::IDY, 5}; // EOR - "Exclusive OR" Memory with Accumulator | Absolute | Opcode: $51
    lookupTable[82] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[83] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[84] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[85] = {"EOR", &Cpu::EOR, &Cpu::ZPX, 4}; // EOR - "Exclusive OR" Memory with Accumulator | X-Indexed Zero Page | Opcode: $55
    lookupTable[86] = {"LSR", &Cpu::LSR, &Cpu::ZPX, 6}; // LSR - Logical Shift Right | X-Indexed Zero Page | Opcode: $56
    lookupTable[87] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[88] = {"CLI", &Cpu::CLI, &Cpu::IMP, 2}; // CLI - Clear Interrupt Disable | Implied | Opcode: $58
    lookupTable[89] = {"EOR", &Cpu::EOR, &Cpu::ZPY, 4}; // EOR - "Exclusive OR" Memory with Accumulator | Y-Indexed Absolute | Opcode: $59
    lookupTable[90] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[91] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[92] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[93] = {"EOR", &Cpu::EOR, &Cpu::ABX, 4}; // EOR - "Exclusive OR" Memory with Accumulator | X-Indexed Absolute | Opcode: $5D
    lookupTable[94] = {"LSR", &Cpu::LSR, &Cpu::ABX, 7}; // LSR - Logical Shift Right | X-Indexed Absolute | Opcode: $5E
    lookupTable[95] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 6
    lookupTable[96] = {"RTS", &Cpu::RTS, &Cpu::IMP, 6}; // RTS - Return From Subroutme | Implied | Opcode: $60
    lookupTable[97] = {"ADC", &Cpu::ADC, &Cpu::IDX, 6}; // ADC - Add Memory to Accumulator with Carry | X-Indexed Zero Page Indirect | Opcode: $61
    lookupTable[98] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[99] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[100] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[101] = {"ADC", &Cpu::ADC, &Cpu::ZPG, 3}; // ADC - Add Memory to Accumulator with Carry | Zero Page | Opcode: $65
    lookupTable[102] = {"ROR", &Cpu::ROR, &Cpu::ZPG, 5}; // ROR - Rotate Right | Zero Page | Opcode: $66
    lookupTable[103] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[104] = {"PLA", &Cpu::PLA, &Cpu::IMP, 4}; // PLA - Pull Accumulator From Stack | Implied | Opcode: $68
    lookupTable[105] = {"ADC", &Cpu::ADC, &Cpu::IMM, 2}; // ADC - Add Memory to Accumulator with Carry | Immediate | Opcode: $69
    lookupTable[106] = {"ROR", &Cpu::ROR, &Cpu::ACC, 2}; // ROR - Rotate Right | Accumulator | Opcode: $6A
    lookupTable[107] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[108] = {"JMP", &Cpu::JMP, &Cpu::IND, 5}; // JMP - JMP Indirect | Absolute Indirect | Opcode: $6C
    lookupTable[109] = {"ADC", &Cpu::ADC, &Cpu::ABS, 4}; // ADC - Add Memory to Accumulator with Carry | Absolute | Opcode: $6D
    lookupTable[110] = {"ROR", &Cpu::ROR, &Cpu::ABS, 6}; // ROR - Rotate Right | Absolute | Opcode: $6E
    lookupTable[111] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial


    // Row 7
    lookupTable[112] = {"BVS", &Cpu::BVS, &Cpu::REL, 2}; // BVS - Branch on Overflow Set | Relative | Opcode: $70
    lookupTable[113] = {"ADC", &Cpu::ADC, &Cpu::IDY, 5}; // ADC - Add Memory to Accumulator with Carry | Zero Page Indirect Y-Indexed | Opcode: $71
    lookupTable[114] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[115] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[116] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[117] = {"ADC", &Cpu::ADC, &Cpu::ZPX, 4}; // ADC - Add Memory to Accumulator with Carry | X-Indexed Zero Page | Opcode: $75
    lookupTable[118] = {"ROR", &Cpu::ROR, &Cpu::ZPX, 6}; // ROR - Rotate Right | X-Indexed Zero Page | Opcode: $76
    lookupTable[119] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[120] = {"SEI", &Cpu::SEI, &Cpu::IMP, 2}; // SEI - Set Interrupt Disable | Implied | Opcode: $78
    lookupTable[121] = {"ADC", &Cpu::ADC, &Cpu::ABY, 4}; // ADC - Add Memory to Accumulator with Carry | Y-Indexed Absolute | Opcode: $79
    lookupTable[122] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[123] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[124] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[125] = {"ADC", &Cpu::ADC, &Cpu::ABX, 4}; // ADC - Add Memory to Accumulator with Carry | X-Indexed Absolute | Opcode: $7D
    lookupTable[126] = {"ROR", &Cpu::ROR, &Cpu::ABX, 7}; // ROR - Rotate Right | X-Indexed Absolute | Opcode: $7E
    lookupTable[127] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 8
    lookupTable[128] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[129] = {"STA", &Cpu::STA, &Cpu::IDX, 6}; // STA - Store Accumulator in Memory | X-Indexed Zero Page Indirect | Opcode: $81
    lookupTable[130] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[131] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[132] = {"STY", &Cpu::STY, &Cpu::ZPG, 3}; // STA - Store Accumulator in Memory | Zero Page | Opcode: $84
    lookupTable[133] = {"STA", &Cpu::STA, &Cpu::ZPG, 3}; // STA - Store Accumulator in Memory | Zero Page | Opcode: $85
    lookupTable[134] = {"STX", &Cpu::STX, &Cpu::ZPG, 3}; // STA - Store Accumulator in Memory | Zero Page | Opcode: $86
    lookupTable[135] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[136] = {"DEY", &Cpu::DEY, &Cpu::IMP, 2}; // DEY - Decrement Index Register Y By One | Implied | Opcode: $88
    lookupTable[137] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[138] = {"TXA", &Cpu::TXA, &Cpu::IMP, 2}; // TXA - Transfer Index X To Accumulator | Implied | Opcode: $8A
    lookupTable[139] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[140] = {"STY", &Cpu::STY, &Cpu::ABS, 4}; // STA - Store Accumulator in Memory | Absolute | Opcode: $8C
    lookupTable[141] = {"STA", &Cpu::STA, &Cpu::ABS, 4}; // STA - Store Accumulator in Memory | Absolute | Opcode: $8D
    lookupTable[142] = {"STX", &Cpu::STX, &Cpu::ABS, 4}; // STA - Store Accumulator in Memory | Absolute | Opcode: $8E
    lookupTable[143] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 9
    lookupTable[144] = {"BCC", &Cpu::BCC, &Cpu::REL, 2}; // BCC - Branch on Carry Clear | Relative | Opcode: $90
    lookupTable[145] = {"STA", &Cpu::STA, &Cpu::IDY, 6}; // STA - Store Accumulator in Memory | Y-Indexed Zero Page Indirect | Opcode: $91
    lookupTable[146] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[147] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[148] = {"STY", &Cpu::STY, &Cpu::ZPX, 4}; // STA - Store Accumulator in Memory | X-Indexed Zero Page | Opcode: $94
    lookupTable[149] = {"STA", &Cpu::STA, &Cpu::ZPX, 4}; // STA - Store Accumulator in Memory | X-Indexed Zero Page | Opcode: $95
    lookupTable[150] = {"STX", &Cpu::STX, &Cpu::ZPY, 4}; // STA - Store Accumulator in Memory | Y-Indexed Zero Page | Opcode: $96
    lookupTable[151] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[152] = {"TYA", &Cpu::TYA, &Cpu::IMP, 2}; // TYA - Transfer Index Y To Accumulator | Implied | Opcode: $98
    lookupTable[153] = {"STA", &Cpu::STA, &Cpu::ABY, 4}; // STA - Store Accumulator in Memory | Y-Indexed Absolute | Opcode: $99
    lookupTable[154] = {"TXA", &Cpu::TXS, &Cpu::IMP, 2}; // TXS - Transfer Index X To Stack Pointer | Implied | Opcode: $9A
    lookupTable[155] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[156] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[157] = {"STA", &Cpu::STA, &Cpu::ABX, 5}; // STA - Store Accumulator in Memory | X-Indexed Absolute | Opcode: $9D
    lookupTable[158] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[159] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 10 (A)
    lookupTable[160] = {"LDY", &Cpu::LDY, &Cpu::IMM, 2}; // LDY - Load Index Register Y From Memory | Immediate | Opcode: $A0
    lookupTable[161] = {"LDA", &Cpu::LDA, &Cpu::IDX, 6}; // LDA - Load Accumulator with Memory | X-Indexed Zero Page Indirect | Opcode: $A1
    lookupTable[162] = {"LDX", &Cpu::LDX, &Cpu::IMM, 2}; // LDX - Load Index Register X From Memory | Immediate | Opcode: $A2
    lookupTable[163] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[164] = {"LDY", &Cpu::LDY, &Cpu::ZPG, 3}; // LDY - Load Index Register Y From Memory | Zero Page | Opcode: $A4
    lookupTable[165] = {"LDA", &Cpu::LDA, &Cpu::ZPG, 3}; // LDA - Load Accumulator with Memory | Zero Page | Opcode: $A5
    lookupTable[166] = {"LDX", &Cpu::LDX, &Cpu::ZPG, 3}; // LDX - Load Index Register X From Memory | Zero Page | Opcode: $A6
    lookupTable[167] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[168] = {"TAY", &Cpu::TAY, &Cpu::IMP, 2}; // TAY - Transfer Accumulator To Index Y | Implied | Opcode: $A8
    lookupTable[169] = {"LDA", &Cpu::LDA, &Cpu::IMM, 2}; // LDA - Load Accumulator with Memory | Immediate | Opcode: $A9
    lookupTable[170] = {"TAX", &Cpu::TAX, &Cpu::IMP, 2}; // TAX - Transfer Accumulator To Index X | Implied | Opcode: $AA
    lookupTable[171] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[172] = {"LDY", &Cpu::LDY, &Cpu::ABS, 4}; // LDY - Load Index Register Y From Memory | Absolute | Opcode: $AC
    lookupTable[173] = {"LDA", &Cpu::LDA, &Cpu::ABS, 4}; // LDA - Load Accumulator with Memory | Absolute | Opcode: $AD
    lookupTable[174] = {"LDX", &Cpu::LDX, &Cpu::ABS, 4}; // LDX - Load Index Register X From Memory | Absolute | Opcode: $AE
    lookupTable[175] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 11 (B)
    lookupTable[176] = {"BCS", &Cpu::BCS, &Cpu::REL, 2}; // BCS - Branch on Carry Set | Relative | Opcode: $B0
    lookupTable[177] = {"LDA", &Cpu::LDA, &Cpu::IDY, 5}; // LDA - Load Accumulator with Memory | Y-Indexed Zero Page Indirect | Opcode: $B1
    lookupTable[178] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[179] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[180] = {"LDY", &Cpu::LDY, &Cpu::ZPX, 4}; // LDY - Load Index Register Y From Memory | X-Indexed Zero Page | Opcode: $B4
    lookupTable[181] = {"LDA", &Cpu::LDA, &Cpu::ZPX, 4}; // LDA - Load Accumulator with Memory | X-Indexed Zero Page | Opcode: $B5
    lookupTable[182] = {"LDX", &Cpu::LDX, &Cpu::ZPY, 4}; // LDX - Load Index Register X From Memory | Y-Indexed Zero Page | Opcode: $B6
    lookupTable[183] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[184] = {"CLV", &Cpu::CLV, &Cpu::IMP, 2}; // CLV - Clear Overflow Flag | Implied | Opcode: $B8
    lookupTable[185] = {"LDA", &Cpu::LDA, &Cpu::ABY, 4}; // LDA - Load Accumulator with Memory | Y-Indexed Absolute | Opcode: $B9
    lookupTable[186] = {"TSX", &Cpu::TSX, &Cpu::IMP, 2}; // TSX - Transfer Stack Pointer To Index X | Implied | Opcode: $BA
    lookupTable[187] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[188] = {"LDY", &Cpu::LDY, &Cpu::ABX, 4}; // LDY - Load Index Register Y From Memory | X-Indexed Absolute | Opcode: $BC
    lookupTable[189] = {"LDA", &Cpu::LDA, &Cpu::ABX, 4}; // LDA - Load Accumulator with Memory | X-Indexed Absolute | Opcode: $BD
    lookupTable[190] = {"LDX", &Cpu::LDX, &Cpu::ABY, 4}; // LDX - Load Index Register X From Memory | Y-Indexed Absolute | Opcode: $BE
    lookupTable[191] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 12 (C)
    lookupTable[192] = {"CPY", &Cpu::CPY, &Cpu::IMM, 2}; // CPY - Compare Index Register Y To Memory | Immediate | Opcode: $C0
    lookupTable[193] = {"CMP", &Cpu::CMP, &Cpu::IDX, 6}; // CMP - Compare Memory and Accumulator | X-Indexed Zero Page Indirect | Opcode: $C1
    lookupTable[194] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[195] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[196] = {"CPY", &Cpu::CPY, &Cpu::ZPG, 3}; // CPY - Compare Index Register Y To Memory | Zero Page | Opcode: $C4
    lookupTable[197] = {"CMP", &Cpu::CMP, &Cpu::ZPG, 3}; // CMP - Compare Memory and Accumulator | Zero Page | Opcode: $C5
    lookupTable[198] = {"DEC", &Cpu::DEC, &Cpu::ZPG, 5}; // DEC - Decrement Memory By One | Zero Page | Opcode: $C6
    lookupTable[199] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[200] = {"INY", &Cpu::INY, &Cpu::IMP, 2}; // INY - Increment Index Register Y By One | Implied | Opcode: $C8
    lookupTable[201] = {"CMP", &Cpu::CMP, &Cpu::IMM, 2}; // CMP - Compare Memory and Accumulator | Immediate | Opcode: $C9
    lookupTable[202] = {"DEX", &Cpu::DEX, &Cpu::IMP, 2}; // DEX - Decrement Index Register X By One | Implied | Opcode: $CA
    lookupTable[203] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[204] = {"CPY", &Cpu::CPY, &Cpu::IMM, 4}; // CPY - Compare Index Register Y To Memory | Immediate | Opcode: $CC
    lookupTable[205] = {"CMP", &Cpu::CMP, &Cpu::ABS, 4}; // CMP - Compare Memory and Accumulator | Absolute | Opcode: $CD
    lookupTable[206] = {"DEC", &Cpu::DEC, &Cpu::ABS, 6}; // DEC - Decrement Memory By One | Absolute | Opcode: $CE
    lookupTable[207] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 13 (D)
    lookupTable[208] = {"BNE", &Cpu::BNE, &Cpu::REL, 2}; // BNE - Branch on Result Not Zero | Relative | Opcode: $D0
    lookupTable[209] = {"CMP", &Cpu::CMP, &Cpu::IDY, 5}; // CMP - Compare Memory and Accumulator | Y-Indexed Zero Page Indirect | Opcode: $D1
    lookupTable[210] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[211] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[212] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[213] = {"CMP", &Cpu::CMP, &Cpu::ZPX, 4}; // CMP - Compare Memory and Accumulator | X-Indexed Zero Page | Opcode: $D5
    lookupTable[214] = {"DEC", &Cpu::DEC, &Cpu::ZPX, 6}; // DEC - Decrement Memory By One | X-Indexed Zero Page | Opcode: $D6
    lookupTable[215] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[216] = {"CLD", &Cpu::CLD, &Cpu::IMP, 2}; // CLD - Clear Decimal Mode | Implied | Opcode: $D8
    lookupTable[217] = {"CMP", &Cpu::CMP, &Cpu::ABY, 4}; // CMP - Compare Memory and Accumulator | Y-Indexed Absolute | Opcode: $D9
    lookupTable[218] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[219] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[220] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[221] = {"CMP", &Cpu::CMP, &Cpu::ABX, 4}; // CMP - Compare Memory and Accumulator | X-Indexed Absolute | Opcode: $DD
    lookupTable[222] = {"DEC", &Cpu::DEC, &Cpu::ABX, 7}; // DEC - Decrement Memory By One | X-Indexed Absolute | Opcode: $DE
    lookupTable[223] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 14 (E)
    lookupTable[224] = {"CPX", &Cpu::CPX, &Cpu::IMM, 2}; // CPX - Compare Index Register X To Memory | Immediate | Opcode: $E0
    lookupTable[225] = {"SBC", &Cpu::SBC, &Cpu::IDX, 6}; // SBC - Subtract Memory from Accumulator with Borrow | X-Indexed Zero Page Indirect | Opcode: $E1
    lookupTable[226] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[227] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[228] = {"CPX", &Cpu::CPX, &Cpu::ZPG, 3}; // CPX - Compare Index Register X To Memory | Zero Page | Opcode: $E4
    lookupTable[229] = {"SBC", &Cpu::SBC, &Cpu::ZPG, 3}; // SBC - Subtract Memory from Accumulator with Borrow | Zero Page | Opcode: $E5
    lookupTable[230] = {"INC", &Cpu::INC, &Cpu::ZPG, 5}; // INC - Increment Memory By One | Zero Page | Opcode: $E6
    lookupTable[231] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[232] = {"INX", &Cpu::INX, &Cpu::IMP, 2}; // INX - Increment Index Register X By One | Implied | Opcode: $E8
    lookupTable[233] = {"SBC", &Cpu::SBC, &Cpu::IMM, 2}; // SBC - Subtract Memory from Accumulator with Borrow | Immediate | Opcode: $E9
    lookupTable[234] = {"NOP", &Cpu::NOP, &Cpu::IMP, 2}; // NOP - No Operation | Implied | Opcode: $EA
    lookupTable[235] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[236] = {"CPX", &Cpu::CPX, &Cpu::ABS, 4}; // CPX - Compare Index Register X To Memory | Absolute | Opcode: $EC
    lookupTable[237] = {"SBC", &Cpu::SBC, &Cpu::ABS, 4}; // SBC - Subtract Memory from Accumulator with Borrow | Absolute | Opcode: $ED
    lookupTable[238] = {"INC", &Cpu::INC, &Cpu::ABS, 6}; // INC - Increment Memory By One | Absolute | Opcode: $EE
    lookupTable[239] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

    // Row 15 (F)
    lookupTable[240] = {"BEQ", &Cpu::BEQ, &Cpu::REL, 2}; // BEQ - Branch on Result Zero | Relative | Opcode: $F0
    lookupTable[241] = {"SBC", &Cpu::SBC, &Cpu::IDY, 5}; // SBC - Subtract Memory from Accumulator with Borrow | Y-Indexed Zero Page Indirect | Opcode: $F1
    lookupTable[242] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[243] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[244] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[245] = {"SBC", &Cpu::SBC, &Cpu::ZPX, 4}; // SBC - Subtract Memory from Accumulator with Borrow | X-Indexed Zero Page | Opcode: $F5
    lookupTable[246] = {"INC", &Cpu::INC, &Cpu::ZPX, 6}; // INC - Increment Memory By One | X-Indexed Zero Page | Opcode: $F6
    lookupTable[247] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[248] = {"SED", &Cpu::SED, &Cpu::IMP, 2}; // SED - Set Decimal Mode | Implied | Opcode: $F8
    lookupTable[249] = {"SBC", &Cpu::SBC, &Cpu::ABY, 4}; // SBC - Subtract Memory from Accumulator with Borrow | Y-Indexed Absolute | Opcode: $F9
    lookupTable[250] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[251] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[252] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial
    lookupTable[253] = {"SBC", &Cpu::SBC, &Cpu::ABX, 4}; // SBC - Subtract Memory from Accumulator with Borrow | X-Indexed Absolute | Opcode: $FD
    lookupTable[254] = {"INC", &Cpu::INC, &Cpu::ABX, 7}; // INC - Increment Memory By One | X-Indexed Absolute | Opcode: $FE
    lookupTable[255] = {"???", &Cpu::XXX, &Cpu::IMP, 2}; // ??? - Unofficial

}


// Destructor
Cpu::~Cpu() = default;

Byte Cpu::read(Word address) {
    return bus->read(address, false);
}

void Cpu::write(Word address, Byte data) {
    bus->write(address, data);
}

void Cpu::Clock() {

    if(cycles == 0){
        opcode = read(pc);
        pc++;

        cycles = lookupTable[opcode].cycles;

        Byte additionalCycleFromAddress = (this->*lookupTable[opcode].addressMode)();
        Byte additionalCycleFromOpcode = (this->*lookupTable[opcode].opcode)();

        cycles += (additionalCycleFromAddress & additionalCycleFromOpcode);
    }

    cycles--;
}

// Address Mode Definitions
Byte Cpu::ACC(){
    fetched = a;
    return 0;
}

Byte Cpu::ABS(){
    Word lowByte = read(pc);
    pc++;
    Word highByte = read(pc);
    pc++;

    absoluteAddress = (highByte << 8) | lowByte;

    return 0;
}

Byte Cpu::ABX(){
    Word lowByte = read(pc);
    pc++;
    Word highByte = read(pc);
    pc++;

    absoluteAddress = ((highByte << 8) | lowByte) + x;

    if((absoluteAddress & 0xFF00) != (highByte << 8)){
        return 1;
    }
    else{
        return 0;
    }
}

Byte Cpu::ABY(){
    Word lowByte = read(pc);
    pc++;
    Word highByte = read(pc);
    pc++;

    absoluteAddress = ((highByte << 8) | lowByte) + y;

    if((absoluteAddress & 0xFF00) != (highByte << 8)){
        return 1;
    }
    else{
        return 0;
    }
}

Byte Cpu::IMM(){
    absoluteAddress = pc++;
    return 0;
}

Byte Cpu::IMP(){
    fetched = a;
    return 0;
}

Byte Cpu::IND(){
    Word lowByte;
    Word highByte;

    Word lowBytePointer = read(pc);
    pc++;
    Word highBytePointer = read(pc);
    pc++;

    Word tempAddress = (highBytePointer << 8) | lowBytePointer;

    if(lowBytePointer == 0x00FF){
        highByte = read(tempAddress & 0xFF00);
    }
    else{
        highByte = read(tempAddress + 1);
    }

    lowByte = read(tempAddress);

    absoluteAddress = (highByte << 8) | lowByte;

    return 0;
}

Byte Cpu::IDX(){
    Word tempAddress = read(pc);
    pc++;

    Word lowByte = read((Word)(tempAddress + (Word)x) & 0x00FF);
    Word highByte = read((Word)(tempAddress + (Word)x + 1) & 0x00FF);

    absoluteAddress = (highByte << 8) | lowByte;

    return 0;
}

Byte Cpu::IDY(){
    Word tempAddress = read(pc);
    pc++;

    Word lowByte = read(tempAddress & 0x00FF);
    Word highByte = read(tempAddress & 0x00FF);

    absoluteAddress = ((highByte << 8) | lowByte) + y;

    if((absoluteAddress & 0xFF00) != (highByte << 8)){
        return 1;
    }
    else{
        return 0;
    }
}

Byte Cpu::REL(){
    relativeAddress = read(pc);
    pc++;

    if(relativeAddress & 0x80){
        relativeAddress |= 0xFF00;
    }
    return 0;
}

Byte Cpu::ZPG(){
    absoluteAddress = read(pc);
    pc++;
    absoluteAddress &= 0x00FF;
    return 0;
}

Byte Cpu::ZPX(){
    absoluteAddress = (read(pc) + x);
    pc++;
    absoluteAddress &= 0x00FF;
    return 0;
}

Byte Cpu::ZPY(){
    absoluteAddress = (read(pc) + y);
    pc++;
    absoluteAddress &= 0x00FF;
    return 0;
}


// Opcode Definitions

Byte Cpu::ADC(){
    return 0x00;
}

Byte Cpu::AND(){
    return 0x00;
}

Byte Cpu::ASL(){
    return 0x00;
}

Byte Cpu::BCC(){
    return 0x00;
}

Byte Cpu::BCS(){
    return 0x00;
}

Byte Cpu::BEQ(){
    return 0x00;
}

Byte Cpu::BIT(){
    return 0x00;
}

Byte Cpu::BMI(){
    return 0x00;
}

Byte Cpu::BNE(){
    return 0x00;
}

Byte Cpu::BPL(){
    return 0x00;
}

Byte Cpu::BRK(){
    return 0x00;
}

Byte Cpu::BVC(){
    return 0x00;
}

Byte Cpu::BVS(){
    return 0x00;
}

Byte Cpu::CLC(){
    return 0x00;
}

Byte Cpu::CLD(){
    return 0x00;
}

Byte Cpu::CLI(){
    return 0x00;
}

Byte Cpu::CLV(){
    return 0x00;
}

Byte Cpu::CMP(){
    return 0x00;
}

Byte Cpu::CPX(){
    return 0x00;
}

Byte Cpu::CPY(){
    return 0x00;
}

Byte Cpu::DEC(){
    return 0x00;
}

Byte Cpu::DEX(){
    return 0x00;
}

Byte Cpu::DEY(){
    return 0x00;
}

Byte Cpu::EOR(){
    return 0x00;
}

Byte Cpu::INC(){
    return 0x00;
}

Byte Cpu::INX(){
    return 0x00;
}

Byte Cpu::INY(){
    return 0x00;
}

Byte Cpu::JMP(){
    return 0x00;
}

Byte Cpu::JSR(){
    return 0x00;
}

Byte Cpu::LDA(){
    return 0x00;
}

Byte Cpu::LDX(){
    return 0x00;
}

Byte Cpu::LDY(){
    return 0x00;
}

Byte Cpu::LSR(){
    return 0x00;
}

Byte Cpu::NOP(){
    return 0x00;
}

Byte Cpu::ORA(){
    return 0x00;
}

Byte Cpu::PHA(){
    return 0x00;
}

Byte Cpu::PHP(){
    return 0x00;
}

Byte Cpu::PLA(){
    return 0x00;
}

Byte Cpu::PLP(){
    return 0x00;
}

Byte Cpu::ROL(){
    return 0x00;
}

Byte Cpu::ROR(){
    return 0x00;
}

Byte Cpu::RTI(){
    return 0x00;
}

Byte Cpu::RTS(){
    return 0x00;
}

Byte Cpu::SBC(){
    return 0x00;
}

Byte Cpu::SEC(){
    return 0x00;
}

Byte Cpu::SED(){
    return 0x00;
}

Byte Cpu::SEI(){
    return 0x00;
}

Byte Cpu::STA(){
    return 0x00;
}

Byte Cpu::STX(){
    return 0x00;
}

Byte Cpu::STY(){
    return 0x00;
}

Byte Cpu::TAX(){
    return 0x00;
}

Byte Cpu::TAY(){
    return 0x00;
}

Byte Cpu::TSX(){
    return 0x00;
}

Byte Cpu::TXA(){
    return 0x00;
}

Byte Cpu::TXS(){
    return 0x00;
}

Byte Cpu::TYA(){
    return 0x00;
}

Byte Cpu::XXX(){
    return 0x00;
}














