#include"../../../include/components/instructions/op.hpp"


void Op::add() {
    m_rd = m_rs1 + m_rs2;    
}

void Op::sub() {
    m_rd = m_rs1 - m_rs2;
}

void Op::sll() {
    m_rd = m_rs1 << BitsManipulation::takeBits(m_rs2, 0, 4);
}

void Op::slt() {
    if (static_cast<int64_t>(m_rs1) < static_cast<int64_t>(m_rs2)) {
        m_rd = 1;
    } else {
        m_rd = 0;
    }
}


void Op::sltu() {
    if (m_rs1 < m_rs2) {
        m_rd = 1;
    } else {
        m_rd = 0;
    }
}

void Op::xorop() {
    m_rd = m_rs1 ^ m_rs2;
}

void Op::srl() {
    m_rd = m_rs1 >> BitsManipulation::takeBits(m_rs2, 0, 4);
}

// it keeps the sign bit
void Op::sra() {
    m_rd =  (m_rs1 & (static_cast<uint64_t>(1) << 
        (sizeof(uint64_t)*8-1)) | (m_rs1 >> BitsManipulation::takeBits(m_rs2, 0, 4)));
}

void Op::orop() {
    m_rd = m_rs1 | m_rs2;
}

void Op::andop() {
    m_rd = m_rs1 & m_rs2;
}

void Op::execution() {
    switch(m_id) {
    case id_t::kadd:
        add();
        break;
    case id_t::ksub:
        sub();
        break;
    case id_t::ksll:
        sll();
        break;
    case id_t::kslt:
        slt();
        break;
    case id_t::ksltu:
        sltu();
        break;
    case id_t::kxor:
        xorop();
        break;
    case id_t::ksrl:
        srl();
        break;
    case id_t::ksra:
        sra();
        break;
    case id_t::kor:
        orop();
        break;
    case id_t::kand:
        andop();
        break;
    default:
        std::cerr << "Error: no matching in switch cases\n";
        abort();
    }
}









