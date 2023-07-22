#include "../../include/instructions/R-format.hpp"

size_t R::takeRegS1() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

size_t R::takeRegS2() {
    return BitsManipulation::takeBits(m_instruction, 20, 24);
}

size_t R::takeRegD() {
    return BitsManipulation::takeBits(m_instruction, 7, 11);
}

R::id_t R::takeId() {
    return id_t(BitsManipulation::takeBits(m_instruction, 12, 14) |
                (BitsManipulation::takeBits(m_instruction, 30, 31) << 3));
}

void R::readRegister(Registers const &reg) {
    m_rs1 = reg.read(m_index_rs1);
    m_rs2 = reg.read(m_index_rs2);
}

void R::writeBack(Registers &regs) { regs.write(m_index_rd, m_rd); }
