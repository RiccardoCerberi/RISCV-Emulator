#include"../../../include/components/instructions/U-format.hpp"

uint64_t U::takeOffset() {
    return BitsManipulation::extendSign(
        BitsManipulation::takeBits(m_instruction, 12, 31),
        19) << 12;
}

size_t U::takeRd() {
    return BitsManipulation::takeBits(m_instruction, 7,11);
}

void U::writeBack(reg_type& reg) {
    reg[m_index_rd] = m_rd;
}