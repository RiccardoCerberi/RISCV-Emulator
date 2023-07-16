#include"../../../include/components/instructions/Jris.hpp"
#include <cstdint>


// Jris
void Jris::execution() {
    m_rd = m_curr_pc + data_size::kword;
}

// NOTE: the least significant bit is not set to zero,
// as happens with branch or jump, because Jris instructions
// belongs to the I-format
uint64_t Jris::moveNextInstruction() {
    uint64_t next_instruction = (m_rs + m_offset) 
            & (static_cast<uint64_t>(-1) >>  (sizeof(uint64_t)*8 - 1));

    return next_instruction;
}
