#include"../../include/instructions/Jris.hpp"
#include <cstdint>


// Jris
void Jris::execution() {
    m_rd = m_curr_pc + DataSize_t::kword;
}

// NOTE: the least significant bit is not set to zero,
// as happens with branch or jump, because Jris instructions
// belongs to the I-format
Address_t Jris::moveNextInstruction() {
    Address_t next_instruction = (m_rs + m_offset) 
            & (static_cast<Address_t>(-1) << 1);
    return next_instruction;
}
