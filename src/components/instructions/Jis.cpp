#include"../../include/components/Jis.hpp"

#include "../../include/components/Jis.hpp"


// Jump
void Jis::execution() {
    m_reg_save_pcis = BitsManipulation::takeBits(m_instruction, 7, 11);
    // the immediate recevied it's in half word, to report
    // it in byte it's needed a left shifting of 1
    m_immediate =
        BitsManipulation::extendSign(BitsManipulation::takeBits(m_instruction, 21, 30) << 1 | BitsManipulation::takeBits(m_instruction, 20, 20) << 11 |
                   BitsManipulation::takeBits(m_instruction, 12, 19) << 12 | BitsManipulation::takeBits(m_instruction, 31, 31) << 20);
#ifdef DEBUG
    std::binset<data_size::kword> is_bin(is);
    std::cout << "Instruction: " << is_bin << "\nImmediate=" << imm << "\n";
#endif
}

void Jis::writeBack(reg_type& registers) {
    registers[m_reg_save_pcis] =  + data_size::kword;
}

uint64_t Jis::moveNextInstruction() {
    return m_curr_pc + m_immediate;
}
