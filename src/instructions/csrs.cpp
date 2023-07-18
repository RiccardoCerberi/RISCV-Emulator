#include "../../include/instructions/csrs.hpp"

#include <cstdint>

CSR::CSR(uint32_t const is, uint64_t const pc) : System(is, pc), write_to_reg{true}, 
write_to_csrs{true} {}

bool CSR::isWriteOp() {
    return m_func3 == System::func3_t::kcsrrw || m_func3 == System::func3_t::kcsrrwi;
}

void CSR::readRegister(reg_type const& reg) {
    m_second_operand = BitsManipulation::takeBits(m_instruction, 15, 19);
    if (m_second_operand == 0 && isWriteOp()==false) {
        write_to_csrs = false;
    }
    if (isWriteOp()==true && m_index_rd ==0) {
        write_to_reg = false;
    }
    if (static_cast<uint8_t>(m_func3) >= 5) {
        m_second_operand = reg[m_second_operand];
    }
}

void CSR::readCSR(csrs_t const& csrs) { m_csr_rs = csrs[m_func12]; }

void CSR::execution() {
    m_csr_rd = makeCSRResult();
    m_rd = m_csr_rs;
}

void CSR::writeCsr(csrs_t& csrs) {
    if (write_to_csrs == true) csrs[m_func12] = m_csr_rd;
}

void CSR::writeBack(reg_type& reg) {
    if (write_to_reg == true) reg[m_index_rd] = m_rd;
}

uint64_t CSR::makeCSRResult() {
    if (m_func3 == System::func3_t::kcsrrw ||
        m_func3 == System::func3_t::kcsrrwi) {
        return m_second_operand;
    } else if (m_func3 == System::func3_t::kcsrrs ||
               m_func3 == System::func3_t::ksrrsi) {
        return arith(m_csr_rs, m_second_operand, "|");
    } else if (m_func3 == System::func3_t::ksrrc ||
               m_func3 == System::func3_t::kcsrrci) {
        return arith(m_csr_rs, !m_second_operand, "&");
    } else {
        std::cerr << "Error: func3 doesn't match for csrs operations\n";
        abort();
    }
}

