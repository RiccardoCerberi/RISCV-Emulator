#include "../../../include/components/instructions/Jis.hpp"
#include <cstdint>

#define DEBUG

// Jump
uint64_t Jis::takeOffset()
{
    uint8_t pos = 8;

    return BitsManipulation::extendSign(
        BitsManipulation::takeBits(m_instruction, 21, 30) << 1 
        | BitsManipulation::takeBits(m_instruction, 20, 20) << 11 
        | BitsManipulation::takeBits(m_instruction, 12, 19) << 12 
        | BitsManipulation::takeBits(m_instruction, 31, 31) << 20, 
        pos
    ) << 1; // shifting required: it's in half word
}

size_t Jis::takeIndexRd()
{
    return BitsManipulation::takeBits(m_instruction, 7, 11);
}

void Jis::execution()
{}

void Jis::writeBack(reg_type &registers)
{
#ifdef DEBUG
    std::cout << printRegIndex(m_index_rd) 
              << " = "
              << m_curr_pc
              << " + "
              << data_size::kword
              << std::endl;
#endif
    registers[m_index_rd] = m_curr_pc + data_size::kword;
}

uint64_t Jis::moveNextInstruction()
{
    uint64_t next_instruction = m_curr_pc + m_offset;
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
