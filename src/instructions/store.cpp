#include "store.hpp"

void Store::readRegister(Registers const& reg) {
    m_rs1 = reg.read(m_index_rs1);
    m_rs2 = reg.read(m_index_rs2);
}

void Store::execution() { m_ad_write = m_rs1 + m_offset; }

void Store::accessMemory(SystemInterface& bus) {
    if (m_func3 > 2) {
        std::cerr << "Invalid data size for store instruction\n";
        abort();
    }
    bus.writeData(m_ad_write, m_rs2, DataSize_t(1 << (m_func3)));
}

size_t Store::takeIndexRS1() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

size_t Store::takeIndexRS2() {
    return BitsManipulation::takeBits(m_instruction, 20, 24);
}

Address_t Store::takeOffset() {
    return BitsManipulation::extendSign(
        BitsManipulation::takeBits(m_instruction, 7, 11) |
            (BitsManipulation::takeBits(m_instruction, 25, 31) << 5),
        11);
}

uint8_t Store::takeFunc3() {
    return BitsManipulation::takeBits(m_instruction, 12, 14);
}
