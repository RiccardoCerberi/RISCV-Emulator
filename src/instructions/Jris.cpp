#include"I-format.hpp"

// Jris
void Jris::execution() {
    m_rd = m_curr_pc + DataSize_t::kword;
}

// NOTE: the least significant bit is not set to zero,
// as happens with branch or jump, because Jris instructions
// belongs to the I-format
Address_t Jris::moveNextInstruction() {
    Address_t next_instruction = (m_rs + m_offset) 
            & (~1); // set last digit to 0
    return next_instruction;
}
