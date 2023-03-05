#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <cassert>
#include "constants.hpp"
#include "bits-manipulation.hpp"

/*
    DRAM is implemented as a vector of SIZE_DRAM bits.
    The size is big enough to lead a segmentation fault if it was allocated in the stack, therefore a heap allocation
    si required.
    DRAM represents the memory to store data related to every process.
    The model adopted is little-endian (the same as x86 systems), that means
the most significant byte is stored at the highest address and the least
significant byte at the lowest. Therefore, if we had to store 0x01[...]04 in
memory, we would have this memory model: 0x0[...]0 | 0x04 |
            ...   | ...  |
        0x0[...]1 | 0x01 |
The opposite model is big-endian.
The first DRAM address is 0x8[...]0 (DRAM_BASE) that is pointed by the pc.
DRAM, which is defined as a vector, starts at 0 index position, hence every address that refers to data in memory should
 be treated relative to DRAM_BASE.
*/

class DRAM
{
public:
    DRAM();

    void store(uint64_t, uint64_t, data_size);
    uint64_t load(uint64_t, data_size);
private:
    std::vector<uint8_t> m_dram;
};