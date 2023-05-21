//
// Created by jacob on 5/20/2023.
//

#pragma once
#include "Cpu.h"
#include <cstdint>
#include <array>

using Byte = uint8_t;
using Word = uint16_t;

class Bus {

public:
    Bus();
    ~Bus();

    Cpu cpu;

    std::array<Byte, 64 * 1024> ram;

    void write(Word address, Byte data);
    Byte read(Word address, bool bReadyOnly = false);
};



