#include"../../../include/components/instructions/imm-op.hpp"

void ImmOp::addi() {
#ifdef DEBUG  
    std::cout << "X" << m_index_rd << " = "
              << "X" << m_index_rs << " + " << m_offset
              << std::endl;
#endif
    m_rd = m_rs + m_offset;
}

void ImmOp::slti() {
#ifdef DEBUG
    std::cout << "(sign extended) X" << m_index_rs
              << " < "
              << m_offset
              << std::endl;
#endif

    if (static_cast<int64_t>(m_rs) < static_cast<int64_t>(m_offset)) {
        m_rd = 1;
    } else  {
        m_rd = 0;
    }
}

void ImmOp::sltiu() {
#ifdef DEBUG
    std::cout << "(unsigned) X" << m_index_rs
              << " < "
              << m_offset
              << std::endl;
#endif

    if (m_rs < m_offset) {
        m_rd = 1;
    } else {
        m_rd = 0;
    }
}

void ImmOp::xori() {
#ifdef DEBUG
    std::cout << "X" << m_index_rs
              << " ^ "
              << m_offset 
              << std::endl;
#endif
    m_rd = m_rs ^ m_offset;
}


void ImmOp::ori() {
#ifdef DEBUG
    std::cout << "X" << m_index_rs
              << " | "
              << m_offset 
              << std::endl;
#endif
    m_rd = m_rs | m_offset;
}

void ImmOp::andi() {
#ifdef DEBUG
    std::cout << "X" << m_index_rs
              << " & "
              << m_offset 
              << std::endl;
#endif
    m_rd = m_rs & m_offset;
}

void ImmOp::slli() {
#ifdef DEBUG
    std::cout << "X" << m_index_rs
              << "  "
              << m_offset 
              << std::endl;
#endif
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = m_rs << shamt;
}

void ImmOp::srli() {
#ifdef DEBUG
    std::cout << "X" << m_index_rs
              << " | "
              << m_offset 
              << std::endl;
#endif
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = m_rs >> shamt;
}

void ImmOp::srai() {
#ifdef DEBUG
    std::cout << "X" << m_index_rs
              << " | "
              << m_offset 
              << std::endl;
#endif
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

