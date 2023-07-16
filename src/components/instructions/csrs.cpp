#include"../../../include/components/instructions/csrs.hpp"
#include <cstdint>

CSR::CSR(uint32_t const is, uint64_t const pc) 
        : System(is,pc), m_index_csr(m_func12)
    {
        // distinguish between immediate and non operations
        if (static_cast<uint8_t>(m_func3) < 5) { 
            m_csr_aux = new CSRImm(m_func3, BitsManipulation::takeBits(is,15,19));
        } else {
            m_csr_aux = new CSRNotImm(m_func3, BitsManipulation::takeBits(is,15,19));
        }
    }

void CSR::readRegister(reg_type const& reg) { 
    m_csr_aux->InterpretQty(reg);
}
    
void CSR::readCSR( csrs_t const& csrs) {
    m_csr_rs = csrs[m_index_csr];
}

void CSR::execution() {
    m_csr_rd = m_csr_aux->makeCSRResult(m_csr_rs);
    m_rd = m_csr_rs;  // always present, maybe with t
}

void CSR::writeCsr(csrs_t& csrs) {
    csrs[m_index_csr] = m_csr_rd;
}

void CSR::writeBack(reg_type &reg) {
    reg[m_index_rd] = m_rd;
}

// CSR not immediate members

void CSRNotImm::InterpretQty( reg_type const & reg) {
    m_rs1 = reg[m_qty];
}

uint64_t CSRNotImm::makeCSRResult(uint64_t const csr_rs) {
    uint64_t result = 0;
    switch(m_func3) {
        case func3_t::kcsrrw:
            result = csrrw(csr_rs);
            break;
        case func3_t::kcsrrs:
            result = csrrs(csr_rs);
            break;
        case func3_t::ksrrc:
            result = csrrc(csr_rs);
            break;
        default:
            std::cerr << "Error: csrs not immediate cases not covered\n";
            abort();
    }
    return result;
}

uint64_t CSRNotImm::csrrw(uint64_t const) {
    return m_rs1;  
}

uint64_t CSRNotImm::csrrs(uint64_t const csr_rs) {
    return csr_rs | m_rs1;
}

uint64_t CSRNotImm::csrrc(uint64_t const csr_rs) {
    return csr_rs & (!(m_rs1));  
}

//Immediate members

void CSRImm::InterpretQty(reg_type const&) {
    m_imm = static_cast<uint64_t>(m_imm);
}

uint64_t CSRImm::makeCSRResult(uint64_t const csr_rs) {
    switch(m_func3) {
        case func3_t::kcsrrwi:
            return csrrwi(csr_rs);
        case func3_t::ksrrsi:
            return csrrsi(csr_rs);
        case func3_t::kcsrrci:
            return csrrci(csr_rs);
        default:
            std::cerr << "Error in CSRImm member function: m_func3 didn't match previous case\n";
            abort();
    }
}

// I could have used arith function
uint64_t CSRImm::csrrwi(uint64_t const) {
    return m_imm;
}

uint64_t CSRImm::csrrsi(uint64_t const csr_rs) {
    return csr_rs | m_imm;
}

uint64_t CSRImm::csrrci(uint64_t const csr_rs) {
    return csr_rs & (!m_imm);
}

