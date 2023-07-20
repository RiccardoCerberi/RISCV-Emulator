#include"../../include/instructions/Jris.hpp"
#include <cstdint>


// Jris
void Jris::execution() {
    m_rd = m_curr_pc + DataSize_t::kword;
}

// NOTE: the least significant bit is not set to zero,
// as happens with branch or jump, because Jris instructions
// belongs to the I-format
InstructionSize_t Jris::moveNextInstruction() {
    InstructionSize_t next_instruction = (m_rs + m_offset) 
            & (static_cast<InstructionSize_t>(-1) << 1);
    return next_instruction;
}
