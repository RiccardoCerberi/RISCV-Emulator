#include "../../include/instructions/system.hpp"

#include <cstdint>

size_t System::takeRd() {
    return BitsManipulation::takeBits(m_instruction, 7, 11);
}

uint8_t System::takeQty() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

System::func3_t System::takeFunc3() {
    return func3_t(BitsManipulation::takeBits(m_instruction, 12, 14));
}

uint16_t System::takeFunc12() {
    return BitsManipulation::takeBits(m_instruction, 20, 31);
}
