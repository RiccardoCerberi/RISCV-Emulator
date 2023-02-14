#include"../../../include/components/instructions"

size_t System::takeRd() {
    return BitsManipulation::takeBits(m_instruction,7,11);
}

size_t System::takeRs1() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

func3_t System::takeFunc3() {
    return func3_t(BitsManipulation::takeBits(m_instruction, 12, 14));
}

uint16_t System::takeFunc12() {
    return BitsManipulation::takeBits(m_instruction, 20, 31);
}

