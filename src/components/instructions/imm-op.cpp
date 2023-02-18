#include"../../../include/components/instructions/imm-op.hpp"

void ImmOp::addi() {
    m_rd = m_rs + m_offset;
}

void ImmOp::slti() {
    if (static_cast<int64_t>(m_rs) < static_cast<int64_t>(m_offset)) {
        m_rd = 1;
    } else  {
        m_rd = 0;
    }
}

void ImmOp::sltiu() {
    if (m_rs < m_offset) {
        m_rd = 1;
    } else {
        m_rd = 0;
    }
}

void ImmOp::xori() {
    m_rd = m_rs ^ m_offset;
}


void ImmOp::ori() {
    m_rd = m_rs | m_offset;
}

void ImmOp::andi() {
    m_rd = m_rs & m_offset;
}

void ImmOp::slli() {
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = m_rs << shamt;
}

void ImmOp::srli() {
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = m_rs >> shamt;
}

void ImmOp::srai() {
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    uint64_t vacant_bit = static_cast<uint64_t>(1) << (sizeof(uint64_t)*8 -1);
    m_rd = (vacant_bit & m_rs) | (m_rs >> shamt);
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
        case id_t::ksrai:
            srai();
            break;
        default:
            std::cerr << "Error: input no matching cases\n";
            abort();
    }
}

