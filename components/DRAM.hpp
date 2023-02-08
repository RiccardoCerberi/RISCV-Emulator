#ifndef DRAM_HPP
#define DRAM_HPP

#include <array>
#include <cstdint>
#include <cstdio>
#include "constants.hpp"


#define DEBUG

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


class DRAM {
public:
    DRAM();

    void store(uint64_t, uint64_t, size_t);
    uint64_t load(uint64_t, size_t);


#ifdef DEBUG
    // function to know till the instructions are stored in dram
    void setLastInstructionAddress(uint64_t);
    // to print out data formatted it should be enough the << operator
    void printInstructionsMemory();
#endif

private:
    uint8_t store_byte(uint64_t,uint64_t, size_t);
    uint8_t store_half_word(uint64_t, uint64_t, size_t);
    uint8_t store_word(uint64_t, uint64_t, size_t);
    uint8_t store_double_word(uint64_t, uint64_t, size_t);

    uint64_t load_byte(uint64_t, size_t);
    uint64_t load_half_word(uint64_t, size_t);
    uint64_t load_word(uint64_t, size_t);
    uint64_t load_double_word(uint64_t, size_t);

    std::array<uint64_t, dram_costants::dram_size> m_dram;
#ifdef DEBUG
    uint64_t m_last_instruction_address;
#endif
};

#endif
