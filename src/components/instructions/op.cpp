#include"../../../src/components/instructions/op.hpp"


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

void Op::xor() {
    m_rd = m_rs1 ^ m_rs2;
}

void Op::srl() {
    m_rd = m_rs1 >> BitsManipulation::takeBits(m_rs2, 0, 4);
}

void Op::sra() {
    m_rd =  (m_rs1 & (1 << (sizeof(uint64_t)*8-1)) | (m_rs1 >> BitsManipulation::takeBits(m_rs2, 0, 4));
}

void Op::or() {
    m_rd = m_rs1 | m_rs2;
}

void Op::and() {
    m_rd = m_rs1 & m_rs2;
}

void Op::execution() {
    switch(m_id) {
    case kadd:
        add();
        break;
    case ksub;
        sub();
        break;
    case ksll:
        sll();
        break;
    case kslt:
        slt();
        break;
    case ksltu:
        sltu();
        break;
    case kxor:
        xor();
        break;
    case ksrl:
        srl();
        break;
    case ksra:
        sra();
        break;
    case kor:
        or();
        break;
    case kand:
        and();
        break;
    default:
        std::cerr << "Error: no matching in switch cases\n";
        abort();
    }
}









