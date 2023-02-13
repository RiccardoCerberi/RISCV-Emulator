#include"../../include/components/instructions/Jris.hpp"


// Jris
void Jris::execution() {
    m_rd = m_curr_pc + data_size::kword;
}

uint64_t Jris::moveNextInstruction() {
    return (m_rs + m_immediate) 
            & (static_cast<uint64_t>(-1) >>  (sizeof(uint64_t)*8 - 1));
}
