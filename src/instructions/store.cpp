#include"../../include/instructions/store.hpp"

void Store::readRegister(Registers const &reg) {
    m_base = reg.read(m_index_base);
    m_src = reg.read(m_index_src);
}

void Store::execution() {
    m_base += m_offset;
}

void Store::accessMemory(SystemInterface& bus) {
    bus.storeData(m_base, m_src, m_width);
}

size_t Store::takeBase() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

size_t Store::takeSrc() {
    return BitsManipulation::takeBits(m_instruction, 20, 24);
}

uint16_t Store::takeOffset() {
    return BitsManipulation::extendSign(
        BitsManipulation::takeBits(m_instruction, 7, 11) 
        | (BitsManipulation::takeBits(m_instruction,25,31)  << 5),
        11);
}

DataSize_t Store::takeWidth() {
    return DataSize_t(BitsManipulation::takeBits(m_instruction,12, 14));
}
    
