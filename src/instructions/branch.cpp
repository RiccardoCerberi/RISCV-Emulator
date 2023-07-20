#include "../../include/instructions/branch.hpp"

size_t Branch::takeRs1() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

size_t Branch::takeRs2() {
    return BitsManipulation::takeBits(m_instruction, 20, 24);
}

uint16_t Branch::takeOffset() {
    const uint8_t last_digit = 12; 
    return BitsManipulation::extendSign(
               (BitsManipulation::takeBits(m_instruction, 8, 11) << 1) |
                   (BitsManipulation::takeBits(m_instruction, 25, 30) << 5) |
                   (BitsManipulation::takeBits(m_instruction, 7, 7) << 11) |
                   (BitsManipulation::takeBits(m_instruction, 31, 31) << 12),
               last_digit);
}

Branch::func3_t Branch::takeFunc3() {
    return func3_t(BitsManipulation::takeBits(m_instruction, 12, 14));
}

void Branch::readRegister(const Registers &reg) {
    m_rs1 = reg.read(m_index_rs1);
    m_rs2 = reg.read(m_index_rs2);
}

void Branch::execution() {
    switch (m_func3) {
        case func3_t::kbeq:
            m_jump = beq();
            break;
        case func3_t::kbne:
            m_jump = bne();
            break;
        case func3_t::kblt:
            m_jump = blt();
            break;
        case func3_t::kbge:
            m_jump = bge();
            break;
        case func3_t::kbltu:
            m_jump = bltu();
            break;
        case func3_t::kbgeu:
            m_jump = bgeu();
            break;
        default:
            std::cerr << "Error: func3 missed\n";
            abort();
    }
}

bool Branch::beq() {
#ifdef DEBUG
    std::cout << printRegIndex(m_index_rs1)
              << " == " << printRegIndex(m_index_rs2) << std::endl;
#endif
    return m_rs1 == m_rs2;
}

bool Branch::bne() {
#ifdef DEBUG
    std::cout << printRegIndex(m_index_rs1)
              << " != " << printRegIndex(m_index_rs2) << std::endl;
#endif
    return m_rs1 != m_rs2;
}

bool Branch::blt() {
#ifdef DEBUG
    std::cout << printRegIndex(m_index_rs1) << " < "
              << printRegIndex(m_index_rs2) << std::endl;
#endif
    return static_cast<int64_t>(m_rs1) < static_cast<int64_t>(m_rs2);
}

bool Branch::bltu() {
#ifdef DEBUG

    std::cout << "(unsigned) " + printRegIndex(m_index_rs1) << " < "
              << printRegIndex(m_index_rs2) << std::endl;
#endif
    return m_rs1 < m_rs2;
}

bool Branch::bge() {
#ifdef DEBUG
    std::cout << "(sign extended) " + printRegIndex(m_index_rs1)
              << " >= " << printRegIndex(m_index_rs2) << std::endl;
#endif
    return static_cast<int64_t>(m_rs1) >= static_cast<int64_t>(m_rs2);
}

bool Branch::bgeu() {
#ifdef DEBUG
    std::cout << "(unsigned) " + printRegIndex(m_index_rs1)
              << " >= " << printRegIndex(m_index_rs2) << std::endl;
#endif
    return m_rs1 >= m_rs2;
}

uint64_t Branch::moveNextInstruction() {
    if (m_jump == true) {
        std::cout << "condition is true\n";
        return m_curr_pc + m_offset;
    }
    std::cout << "condition is false\n";
    return m_curr_pc + DataSize_t::kword;
}
