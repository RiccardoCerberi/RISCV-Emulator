#include "../../../include/components/instructions/Jis.hpp"

#include "../../../include/components/instructions/Jis.hpp"

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
{
#ifdef DEBUG
    std::binset<data_size::kword> is_bin(is);
    std::cout << "Instruction: " << is_bin << "\nImmediate=" << imm << "\n";
#endif
}

void Jis::writeBack(reg_type &registers)
{
    registers[m_index_rd] = +data_size::kword;
}

uint64_t Jis::moveNextInstruction()
{
    return m_curr_pc + m_offset;
}
