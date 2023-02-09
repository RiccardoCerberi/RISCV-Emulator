#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <cassert>
#include "constants.hpp"

/*
    DRAM is implemented as an array of SIZE_DRAM bits.
    DRAM will contain data releated to the processes.
    The model adopted is little-endian (is the one of x86 systems), that means
the most significant byte is stored at the highest address and the least
significant byte at the lowest. Therefore, if we had to store 0x01[...]04 in
memory, we would have this memory model: 0x0[...]0 | 0x04 |
            ...   | ...  |
        0x0[...]1 | 0x01 |
The opposite model is big-endian.
The first DRAM address is 0x8[...]0 (DRAM_BASE) that is pointed by the pci.
DRAM is defined as a vector that starts from 0, hence every address need to be
reduced by DRAM_BASE DRAM is defined as a vector that starts from 0, hence every
address need to be reduced by DRAM_BASE.
*/

class DRAM;


#ifdef DEBUG
// to print out data formatted it should be enough the << operator
void printInstructionsMemory(DRAM const &);
#endif

class DRAM
{
#ifdef DEBUG
    friend void printInstructionsMemory(DRAM const &);
#endif
public:
    DRAM();

    void store(uint64_t, uint64_t, data_size);
    uint64_t load(uint64_t, data_size);

    void setLastInstructionAddress(uint64_t);

private:
    std::vector<uint64_t> m_dram;
    uint64_t m_last_instruction_address;

// variable to know if the variable m_last_instruction_address has already been set to avoid user from wrongly change the variable
// causing data corruption
    bool m_last_instruction_already_set;
};