#include"../../../include/components/instructions/store.hpp"


void Store::readRegister(const reg_type &reg) {
    m_base = reg[m_index_base];
    m_src = reg[m_index_src];
}

void Store::execution() {
    m_base += m_imm ;
}

void Store::accessMemory(Bus& bus) {
    bus.storeData(m_base, m_src, m_width);
}

size_t Store::takeBase() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

size_t Store::takeSrc() {
    return BitsManipulation::takeBits(m_instruction, 20, 24);
}

uint16_t Store::takeImm() {
    return (BitsManipulation::takeBits(m_instruction, 7, 11) | 
(BitsManipulation::takeBits(m_instruction,25,31)  << 5)
            );
}

CPU::data_size Store::takeWidth() {
    return BitsManipulation::takeBits(m_instruction,12, 14);
}
    
