#include "I-format.hpp"

void ImmOp::addi() {
    std::string op = "+";
#ifdef DEBUG
    printInstruction("ADDI", op);
#endif
    m_rd = arith(m_rs, m_offset, op);
}

void ImmOp::slti() {
#ifdef DEBUG
    printInstruction("SLTI", "<");
#endif
    if (static_cast<int32_t>(m_rs) <
        static_cast<int32_t>(BitsManipulation::extendSign(m_offset, 11))) {
        m_rd = 1;
    } else {
        m_rd = 0;
    }
}

void ImmOp::sltiu() {
#ifdef DEBUG
    printInstruction("SLTIU", "<");
#endif

    if (m_rs < m_offset) {
        m_rd = 1;
    } else {
        m_rd = 0;
    }
}

void ImmOp::xori() {
    std::string op = "^";
#ifdef DEBUG
    printInstruction("XORI", op);
#endif
    m_rd = arith(m_rs, m_offset, op);
}

void ImmOp::ori() {
    std::string op = "|";
#ifdef DEBUG
    printInstruction("ORI", op);
#endif
    m_rd = arith(m_rs, m_offset, op);
}

void ImmOp::andi() {
    std::string op = "&";
#ifdef DEBUG
    printInstruction("ANDI", op);
#endif
    m_rd = arith(m_rs, m_offset, op);
}

void ImmOp::slli() {
    std::string op       = "<<";
    RegisterSize_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd                 = arith(m_rs, shamt, op);

#ifdef DEBUG
    // takes only a part of the offset
    auto temp = m_offset;
    m_offset  = shamt;
    printInstruction("SLLI", op);
    m_offset = temp;
#endif
}

void ImmOp::srli() {
    std::string op       = ">>L";
    RegisterSize_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd                 = arith(m_rs, shamt, op);
#ifdef DEBUG
    // takes only a part of the offset
    auto temp = m_offset;
    m_offset  = shamt;
    printInstruction("SRLI", op);
    m_offset = temp;
#endif
}

void ImmOp::srai() {
    std::string op       = ">>A";
    RegisterSize_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd                 = arith(m_rs, shamt, op);
#ifdef DEBUG
    // takes only a part of the offset
    auto temp = m_offset;
    m_offset  = shamt;
    printInstruction("SRAI", op);
    m_offset = temp;
#endif
}

void ImmOp::execution() {
    if (m_func3 == func3_t::kaddi)
        addi();
    else if (m_func3 == func3_t::kslti)
        slti();
    else if (m_func3 == func3_t::ksltiu)
        sltiu();
    else if (m_func3 == func3_t::kxori)
        xori();
    else if (m_func3 == func3_t::kori)
        ori();
    else if (m_func3 == func3_t::kandi)
        andi();
    else if (m_func3 == func3_t::kslli)
        slli();
    else if (m_func3 == func3_t::ksrli &&
             BitsManipulation::takeBits(m_instruction, 30, 31) == 0)
        srli();
    else if (m_func3 == func3_t::ksrai &&
             BitsManipulation::takeBits(m_instruction, 30, 31) == 1)
        srai();
    else {
        std::cerr << "Error: input no matching cases\n";
        abort();
    }
}

void ImmOp::printInstruction(std::string const &is_name,
                             std::string const &op) {
    std::cout << is_name << " " << printRegIndex(m_index_rd) << " = "
              << printRegIndex(m_index_rs) << " " << op << " " << m_offset
              << std::endl;
}
