#include"../../../include/components/instructions/Jris.hpp"


// Jris
void Jris::execution() {
    m_rd = m_curr_pc + data_size::kword;
}

uint64_t Jris::moveNextInstruction() {
    // NOTE: the least significant bit is not set to zero,
    // as happens with branch or jump, because Jris instructions
    // belongs to the I-format
    return (m_rs + m_offset) 
            & (static_cast<uint64_t>(-1) >>  (sizeof(uint64_t)*8 - 1));
}
