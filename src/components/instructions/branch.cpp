#include"../../../include/components/instructions/branch.hpp"


size_t Branch::takeRs1() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

size_t Branch::takeRs2() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

uint16_t Branch::takeOffset() {
    // NOTE: shifting starts from 1 because the offset in the instruction is in half word
    return BitsManipulation::extendSign((BitsManipulation::takeBits(m_instruction, 8, 11))
        | (BitsManipulation::takeBits(m_instruction, 25, 30) << 4)
        | (BitsManipulation::takeBits(m_instruction, 7,7) << 10)
        | (BitsManipulation::takeBits(m_instruction, 31,31) << 11),
        11) << 1;
}
    
Branch::id_t Branch::takeIdCond() {
    return id_t(BitsManipulation::takeBits(m_instruction,12,14));
}

void Branch::readRegister(const reg_type &reg) {
    m_rs1 = reg[m_index_rs1];
    m_rs2 = reg[m_index_rs2];
}

void Branch::execution() {
    switch(m_id_cond) {
        case id_t::kbeq:
            m_jump = beq();
            break;
        case id_t::kbne:
            m_jump = bne();
            break;
        case id_t::kblt:
            m_jump = blt();
            break;
        case id_t::kbge:
            m_jump = bge();
            break;
        case id_t::kbltu:
            m_jump = bltu();
            break;
        case id_t::kbgeu:
            m_jump = bgeu();
            break;
        default:
            std::cerr << "Error: there must be a match\n";
    }
}

bool Branch::beq() {
#ifdef DEBUG
    std::cout << "X" << m_index_rs1 
              << " == " <<
              << "X" << m_index_rs2
              << std::endl;
#endif
    return m_rs1 == m_rs2;
}

bool Branch::bne() {
#ifdef DEBUG
    std::cout << "X" << m_index_rs1 
              << " != " <<
              << "X" << m_index_rs2
              << std::endl;
#endif
    return m_rs1 != m_rs2;
}

bool Branch::blt() {
#ifdef DEBUG
    std::cout << "(sign extended) X" << m_index_rs1 
              << " < " <<
              << "X" << m_index_rs2
              << std::endl;
#endif
    return static_cast<int64_t>(m_rs1) < static_cast<int64_t>(m_rs2);
}

bool Branch::bltu() {
#ifdef DEBUG
    std::cout << "(unsigned) X" << m_index_rs1 
              << " < " <<
              << "X" << m_index_rs2
              << std::endl;
#endif
    return m_rs1 < m_rs2;
}

bool Branch::bge() {
#ifdef DEBUG
    std::cout << "(sign extended) X" << m_index_rs1 
              << " >= " <<
              << "X" << m_index_rs2
              << std::endl;
#endif
    return static_cast<int64_t>(m_rs1) >= static_cast<int64_t>(m_rs2);
}

bool Branch::bgeu() {
#ifdef DEBUG
    std::cout << "(unsigned) X" << m_index_rs1 
              << " >= " <<
              << "X" << m_index_rs2
              << std::endl;
#endif
    return m_rs1 >= m_rs2;
}

uint64_t Branch::moveNextInstruction() {
    if (m_jump == true) {
        std::cout << "condition is true\n";
        return m_curr_pc + m_offset;
    } 
    std::cout << "condition is false\n";
    return m_curr_pc + data_size::kword;
}


         void printRdIndex() override;
         void printRs1Index() override;        
         void printRs2Index() override;