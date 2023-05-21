//
// Created by jacob on 5/20/2023.
//

#include "Bus.h"

Bus::Bus() {
    for(auto &i : ram) i = 0x00; // Sets all address locations to 0
    cpu.ConnectBus(this);
}

Bus::~Bus() {}

void Bus::write(Word address, Byte data) {
    if(address >= 0x0000 && address <= 0xFFFF){
        ram[address] = data;
    }
}

Byte Bus::read(Word address, bool bReadyOnly) {
    if(address >= 0x0000 && address <= 0xFFFF){
        return ram[address];
    }
    return 0x00;
}
