#include "DRAM.hpp"

DRAM::DRAM() {
    m_dram[ZERO] = 0;
    m_dram[SP] = DRAM_BASE + DRAM_SIZE;
}

