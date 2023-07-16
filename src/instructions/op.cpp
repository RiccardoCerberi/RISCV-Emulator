#include"../../include/instructions/op.hpp"


void Op::add() {
    std::string op = "+";
#ifdef DEBUG
    printInstruction("ADD", op);
#endif
    m_rd = arith(m_rs1, m_rs2, op);
}

void Op::sub() {
    std::string op = "-";
#ifdef DEBUG
    printInstruction("SUB", op);
#endif
    m_rd = arith(m_rs1, m_rs2, op);
}

void Op::sll() {
    std::string op = "<<";
    auto lower_five_bits = BitsManipulation::takeBits(m_rs2, 0, 4);
#ifdef DEBUG
    printInstruction("SLL", op)    ;
#endif
    m_rd = arith(m_rs1, lower_five_bits, op);
}

void Op::slt() {
    std::string op = "<<";
#ifdef DEBUG
    printInstruction("SLT", op)    ;
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
    std::string op = "^";
#ifdef DEBUG
    printInstruction("XOROP", op);
#endif
    m_rd = arith(m_rs1,m_rs2, op);
}

void Op::srl() {
    std::string op = ">>";
#ifdef DEBUG
    printInstruction("SRL", op);
#endif
    m_rd = arith(m_rs1, BitsManipulation::takeBits(m_rs2, 0, 4), op);
}

// arithmetic right shift of rs1 by the lower five bits in rs2
void Op::sra() {
    std::string op = ">>";
#ifdef DEBUG
    printInstruction("SRA", op);
#endif
    uint64_t vacant_bit = BitsManipulation::takeVacantBit(m_rs1);
    m_rd = arith(m_rs1, BitsManipulation::takeBits(m_rs2, 0, 4), op) | (vacant_bit);
}

void Op::orop() {
    std::string op = "|";
#ifdef DEBUG
    printInstruction("OROP", op);
#endif
    m_rd = arith(m_rs1,m_rs2, op);
}

void Op::andop() {
    std::string op = "&";
#ifdef DEBUG
    printInstruction("ANDOP", op);
#endif
    m_rd = arith(m_rs1, m_rs2, op);
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

void Op::printInstruction(std::string const &is_name, std::string const& op) {
    std::cout << is_name << " " << printRegIndex(m_index_rd) <<  " = " << printRegIndex(m_index_rs1) << " " << op << " " << printRegIndex(m_index_rs2) << std::endl;
}
