#include"../../../include/components/instructions/I-format.hpp"


size_t I::takeRegS() {
    return BitsManipulation::takeBits(m_instruction,15,19);
}

size_t I::takeRegD(){
    return BitsManipulation::takeBits(m_instruction, 7, 11);
}


uint64_t I::takeOffset()
{
    return BitsManipulation::extendSign(BitsManipulation::takeBits(m_instruction, 20, 31), 11);
}


I::id_t I::takeId() {
    return I::id_t(BitsManipulation::takeBits(m_instruction, 12, 14)
                    | (BitsManipulation::takeBits(m_instruction,30,31) << 3));
}

void I::readRegister(const reg_type & regs) {
    m_rs = regs[m_index_rs];
}

void I::writeBack(reg_type &regs) {
    regs[m_index_rd] = m_rd;
}

