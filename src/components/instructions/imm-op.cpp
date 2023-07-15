#include"../../../include/components/instructions/imm-op.hpp"

void ImmOp::addi() {
#ifdef DEBUG  
    printInstruction("ADDI", "+");
#endif
    m_rd = m_rs + m_offset;
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
#ifdef DEBUG
    printInstruction("XORI", "^");
#endif
    m_rd = m_rs ^ m_offset;
}


void ImmOp::ori() {
#ifdef DEBUG
    printInstruction("ORI", "|");
#endif
    m_rd = m_rs | m_offset;
}

void ImmOp::andi() {
#ifdef DEBUG
    printInstruction("ANDI", "&");
#endif
    m_rd = m_rs & m_offset;
}

void ImmOp::slli() {
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = m_rs << shamt;

#ifdef DEBUG
    // takes only a part of the offset
    auto temp = m_offset;
    m_offset = shamt;
    printInstruction("SLLI", "<<");
    m_offset = temp;
#endif
}

void ImmOp::srli() {
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = m_rs >> shamt;

#ifdef DEBUG
    // takes only a part of the offset
    auto temp = m_offset;
    m_offset = shamt;
    printInstruction("SRLI", ">>");
    m_offset = temp;
#endif
}

void ImmOp::srai() {
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    uint64_t vacant_bit = BitsManipulation::takeVacantBit(m_rs);
    m_rd = (vacant_bit) | (m_rs >> shamt);
#ifdef DEBUG
    // takes only a part of the offset
    auto temp = m_offset;
    m_offset = shamt;
    printInstruction("SRAI", ">>");
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
    std::cout << is_name << " " << printRegIndex(m_index_rd) <<  " = " << printRegIndex(m_index_rs) << " " << op << " " << printRegIndex(m_offset) << std::endl;
}