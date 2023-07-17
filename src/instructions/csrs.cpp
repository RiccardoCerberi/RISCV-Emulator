#include "../../include/instructions/csrs.hpp"

#include <cstdint>

CSR::CSR(uint32_t const is, uint64_t const pc) : System(is, pc) {}

void CSR::readRegister(reg_type const& reg) {
    m_second_operand = BitsManipulation::takeBits(m_instruction, 15, 19);
    // for non immediate function the bits form the register index
    if (static_cast<uint8_t>(m_func3) >= 5)
        m_second_operand = reg[m_second_operand];
}

void CSR::readCSR(csrs_t const& csrs) { m_csr_rs = csrs[m_func12]; }

void CSR::execution() {
    m_csr_rd = makeCSRResult();
    m_rd = m_csr_rs;
}

void CSR::writeCsr(csrs_t& csrs) { csrs[m_func12] = m_csr_rd; }

void CSR::writeBack(reg_type& reg) {
    if (m_index_rd != 0) reg[m_index_rd] = m_rd;
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
        std::cerr << "Error: func3 is invalid\n";
        abort();
    }
}