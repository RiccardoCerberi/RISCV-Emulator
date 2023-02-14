#include"../../../include/components/instructions/csrs.hpp"


void CSR::readRegister(reg_type const& reg) { 
    m_rs1 = reg[m_index_rs1]; 
}
    
void CSR::readCSR(const csrs_t & csrs) {
    m_csr_rs = csrs[m_index_csr];
}

void CSR::execution() {
    switch(m_func3) {
        case func3_t::kcsrrw:
            srrw();
            break;
        case func3_t::kcsrrs:
            srrs();
            break;
        case func3_t::ksrrc:
            srrc();
            break;
        case func3_t::kcsrrwi:
            srrwi();
            break;
        case func3_t::ksrrsi:
            srrsi();
            break;
        case func3_t::kcsrrci:
            srrci();
            break;
        case func3_t::kecall:
            std::cerr << "CSR cannot catch ecall\n";
            break;
        default:
            std::cerr << "No case found for CSR execution\n";
            abort();
    }
}

void CSR::writeBack(reg_type &reg) {
    reg[m_index_rd] = m_rd;
}

void CSR::accessCsr(csrs_t& csrs) {
    csrs[m_index_csr] = m_csr_rd;
}
