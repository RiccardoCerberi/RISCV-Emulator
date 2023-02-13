#include"../../../include/components/instructions/branch.hpp"


size_t Branch::takeRs1() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

size_t takeRs2() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

uint16_t Branch::takeOffset() {
    return 
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

uint64_t Branch::moveNextInstruction() {
    if (m_jump == true)
        return m_current_pc + m_imm;
    return m_current_pc + data_size::kword;
}


bool Branch::beq() {
    return m_rs1 == m_rs2;
}

bool Branch::bne() {
    // analogue to !beq()
    return m_rs1 != m_rs2;
}

bool Branch::blt() {
    return static_cast<int64_t>(m_rs1) < static_cast<int64_t>(m_rs2);
}

bool Branch::bltu() {
    return m_rs1 < m_rs2;
}

bool Branch::bge() {
    return static_cast<int64_t>(m_rs1) >= static_cast<int64_t>(m_rs2);
}

bool Branch::bgeu() {
    return m_rs1 >= m_rs2;
}




