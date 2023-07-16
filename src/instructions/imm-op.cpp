#include"../../../include/components/instructions/imm-op.hpp"

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
    if (static_cast<int64_t>(m_rs) < static_cast<int64_t>(m_offset)) {
        m_rd = 1;
    } else  {
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
    m_rd = arith(m_rs,m_offset, op);
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
    printInstruction("ANDI",op);
#endif
    m_rd = arith(m_rs,m_offset, op);
}

void ImmOp::slli() {
    std::string op = "<<";
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = arith(m_rs,shamt, op);

#ifdef DEBUG
    // takes only a part of the offset
    auto temp = m_offset;
    m_offset = shamt;
    printInstruction("SLLI", op);
    m_offset = temp;
#endif
}

void ImmOp::srli() {
    std::string op = ">>";
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = arith(m_rs, shamt, op);

#ifdef DEBUG
    // takes only a part of the offset
    auto temp = m_offset;
    m_offset = shamt;
    printInstruction("SRLI", op);
    m_offset = temp;
#endif
}

void ImmOp::srai() {
    std::string op = ">>";
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    uint64_t vacant_bit = BitsManipulation::takeVacantBit(m_rs);
    m_rd = (vacant_bit) | arith(m_rs,shamt, op);
#ifdef DEBUG
    // takes only a part of the offset
    auto temp = m_offset;
    m_offset = shamt;
    printInstruction("SRAI", op);
    m_offset = temp;
#endif
}

void ImmOp::execution() {
    // see enum class in switch
    switch(m_id) {
        case id_t::kaddi:
            addi();
            break;
        case id_t::kslti:
            slti();
            break;
        case id_t::ksltiu:
            sltiu();
            break;
        case id_t::kxori:
            xori();
            break;
        case id_t::kori:
            ori();
            break;
        case id_t::kandi:
            andi();
            break;
        case id_t::kslli:
            slli();
            break;
        case id_t::ksrli:
            srli();
            break;
        case id_t::ksrai:
            srai();
            break;
        default:
            std::cerr << "Error: input no matching cases\n";
            abort();
    }
}

void ImmOp::printInstruction(std::string const &is_name, std::string const &op) {
    std::cout << is_name << " " << printRegIndex(m_index_rd) <<  " = " << printRegIndex(m_index_rs) << " " << op << " " << m_offset << std::endl;
}