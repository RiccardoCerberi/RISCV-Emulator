#include "../../include/instructions/Jis.hpp"
#include <cstdint>

// Jump
Address_t Jis::takeOffset()
{
    uint8_t pos = 20;

    return BitsManipulation::extendSign(
        BitsManipulation::takeBits(m_instruction, 21, 30) << 1 // implicit shift done here 
        | BitsManipulation::takeBits(m_instruction, 20, 20) << 11 
        | BitsManipulation::takeBits(m_instruction, 12, 19) << 12 
        | BitsManipulation::takeBits(m_instruction, 31, 31) << 20, 
        pos
    ); 
}

size_t Jis::takeIndexRd()
{
    return BitsManipulation::takeBits(m_instruction, 7, 11);
}

void Jis::execution()
{}

void Jis::writeBack(Registers &regs)
{
#ifdef DEBUG
    std::cout << printRegIndex(m_index_rd) 
              << " = "
              << m_curr_pc
              << " + "
              << DataSize_t::kword
              << std::endl;
#endif
    regs.write(m_index_rd, m_curr_pc + DataSize_t::kword);
}

Address_t Jis::moveNextInstruction()
{
    Address_t next_instruction = m_curr_pc + m_offset;
#ifdef DEBUG
    std::cout << "Next_instruction "
              << " = "
              << m_curr_pc 
              << " + "
              << m_offset
              << std::endl;
#endif
    return next_instruction;
}
