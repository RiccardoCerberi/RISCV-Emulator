#include "R-format.hpp"

size_t R::takeRegS1() {
    return BitsManipulation::takeBits(m_instruction, 15, 19);
}

size_t R::takeRegS2() {
    return BitsManipulation::takeBits(m_instruction, 20, 24);
}

size_t R::takeRegD() {
    return BitsManipulation::takeBits(m_instruction, 7, 11);
}

R::id_t R::takeId() {
    return id_t(BitsManipulation::takeBits(m_instruction, 12, 14) |
                (BitsManipulation::takeBits(m_instruction, 30, 31) << 3));
}

void R::readRegister(Registers const &reg) {
    m_rs1 = reg.read(m_index_rs1);
    m_rs2 = reg.read(m_index_rs2);
}

void R::writeBack(Registers &regs) { regs.write(m_index_rd, m_rd); }


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
    if (static_cast<int32_t>(m_rs1) < static_cast<int32_t>(m_rs2)) {
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
    std::string op = ">>L";
#ifdef DEBUG
    printInstruction("SRL", op);
#endif
    m_rd = arith(m_rs1, BitsManipulation::takeBits(m_rs2, 0, 4), op);
}

void Op::sra() {
    std::string op = ">>A";
#ifdef DEBUG
    printInstruction("SRA", op);
#endif
    m_rd = arith(m_rs1, BitsManipulation::takeBits(m_rs2, 0, 4), op); 
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
