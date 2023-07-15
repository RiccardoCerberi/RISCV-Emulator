#include"../../../include/components/instructions/op.hpp"


void Op::add() {
#ifdef DEBUG
    printInstruction("ADD", "+");
#endif
    m_rd = m_rs1 + m_rs2;    
}

void Op::sub() {
#ifdef DEBUG
    printInstruction("SUB", "-");
#endif
    m_rd = m_rs1 - m_rs2;
}

void Op::sll() {
    auto lower_five_bits = BitsManipulation::takeBits(m_rs2, 0, 4);
#ifdef DEBUG
    printInstruction("SLL", "<<")    ;
#endif
    m_rd = m_rs1 << lower_five_bits;
}

void Op::slt() {
#ifdef DEBUG
    printInstruction("SLT", "<<")    ;
#endif
    if (static_cast<int64_t>(m_rs1) < static_cast<int64_t>(m_rs2)) {
        m_rd = 1;
    } else {
        m_rd = 0;
    }
}


void Op::sltu() {
#ifdef DEBUG
    printInstruction("SLTU", "<<")    ;
#endif
    if (m_rs1 < m_rs2) {
        m_rd = 1;
    } else {
        m_rd = 0;
    }
}

void Op::xorop() {
#ifdef DEBUG
    printInstruction("XOROP", "^");
#endif
    m_rd = m_rs1 ^ m_rs2;
}

void Op::srl() {
#ifdef DEBUG
    printInstruction("SRL", ">>");
#endif
    m_rd = m_rs1 >> BitsManipulation::takeBits(m_rs2, 0, 4);
}

// arithmetic right shift of rs1 by the lower five bits in rs2
void Op::sra() {
#ifdef DEBUG
    printInstruction("SRA", ">>");
#endif
    uint64_t vacant_bit = BitsManipulation::takeVacantBit(m_rs1);
    m_rd = (m_rs1 >> BitsManipulation::takeBits(m_rs2, 0, 4)) | (vacant_bit);
}

void Op::orop() {
#ifdef DEBUG
    printInstruction("OROP", "|");
#endif
    m_rd = m_rs1 | m_rs2;
}

void Op::andop() {
#ifdef DEBUG
    printInstruction("ANDOP", "&");
#endif
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

void Op::printInstruction(std::string const &is_name, std::string const &op) {
    std::cout << is_name << " " << printRegIndex(m_index_rd) <<  " = " << printRegIndex(m_index_rs1) << " " << op << " " << printRegIndex(m_index_rs2) << std::endl;
}
