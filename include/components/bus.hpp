#pragma once

#include "DRAM.hpp"
/*
 * Bus it's the interface between the cpu and dram
*/

/*
 * In the I/O model, the peripherals are mapped to the memory, that means
 * we can access to them using load and store instructions. Therefore, our
 * model will be something like
 *  0x40[...]0 |    Input   |
 *  0x40[...]1 |    Output  |
 *
 *  0x80[...]0 |    DRAM    |
 *
 */

class Bus
{
public:
    uint64_t loadData(uint64_t const, data_size const&);
    void storeData(uint64_t const, uint64_t const, data_size const&);
#ifdef DEBUG
    void printMemory(uint64_t, uint64_t, data_size const&);
#endif

private:
    DRAM m_dram;
};
