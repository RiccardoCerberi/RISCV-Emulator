#include "U-format.hpp"

RegisterSize_t U::takeOffset() {
    return BitsManipulation::extendSign(
               BitsManipulation::takeBits(m_instruction, 12, 31), 19)
           << 12;
}

size_t U::takeRd() { return BitsManipulation::takeBits(m_instruction, 7, 11); }

void U::writeBack(Registers& regs) { regs.write(m_index_rd, m_rd); }

void Auipc::execution() {
    m_rd = m_offset + m_curr_pc;
#ifdef DEBUG
    std::cout << "Auipc:"
              << " offset =  " << m_offset 
              << " current_pc = " << std::hex << m_curr_pc
              << " x" << m_index_rd << " = offset + current_pc = " << std::hex << m_rd 
              << std::dec << std::endl;
#endif
}

void Lui::execution() {
#ifdef DEBUG
    std::cout << "Lui: offset = 0x" <<std::hex<< m_offset << std::dec << std::endl;
#endif
    m_rd = m_offset;
}
