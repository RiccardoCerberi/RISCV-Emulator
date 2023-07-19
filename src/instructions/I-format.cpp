#include "../../include/instructions/I-format.hpp"

size_t I::takeRegS() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

size_t I::takeRegD() {
    return BitsManipulation::takeBits(m_instruction, 7, 11);
}

uint64_t I::takeOffset() {
    return BitsManipulation::extendSign(
        BitsManipulation::takeBits(m_instruction, 20, 31), 11);
}

I::func3_t I::takeFunc3() {
    return func3_t(BitsManipulation::takeBits(m_instruction, 12, 14));
}

void I::readRegister(Registers const &regs) { m_rs = regs.read(m_index_rs); }

void I::writeBack(Registers &regs) { regs.write(m_index_rd, m_rd); }
