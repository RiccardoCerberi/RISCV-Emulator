#include"../../../include/components/instructions/csrs.hpp"
#include <cstdint>


// error: immediate operations don't read anything from reg: the three bit refer to
// the immediate.
void CSR::readRegister(reg_type const& reg) { 
    m_csr_aux->InterpretQty(reg);
}
    
void CSR::readCSR(const csrs_t & csrs) {
    m_csr_rs = csrs[m_index_csr];
}

void CSR::execution() {
    m_csr_rd = m_csr_aux->makeCSRResult(m_csr_rs);
// TODO: check possible errors because I'm not considering to separate m_csr_rs reading
// and m_rd assingment; in the guide: t = m_csr_rs [...] m_rd = t
    m_rd = m_csr_rs;  // always present, maybe with t
    //    case func3_t::kcsrrwi:
    //        srrwi();
    //        break;
    //    case func3_t::ksrrsi:
    //        srrsi();
    //        break;
    //    case func3_t::kcsrrci:
    //        srrci();
    //        break;
    //    case func3_t::kecall:
    //        std::cerr << "CSR cannot catch ecall\n";
    //        break;
    //    default:
    //        std::cerr << "No case found for CSR execution\n";
    //        abort();
    //}
}

// NOTE: I cut the c from the name of the csrs functions 

// CSR not immediate members


void CSRNotImm::InterpretQty(const reg_type & reg) {
    m_rs1 = reg[m_qty];
}

uint64_t CSRNotImm::makeCSRResult(const uint64_t csr_rs) {
    uint64_t result = 0;
    switch(m_func3) {
        case func3_t::kcsrrw:
            result = srrw(csr_rs);
            break;
        case func3_t::kcsrrs:
            result = srrs(csr_rs);
            break;
        case func3_t::ksrrc:
            result = srrc(csr_rs);
            break;
        default:
            std::cerr << "Error: csrs not immediate cases not covered\n";
            abort();
    }
    return result;
}

uint64_t CSRNotImm::srrw(uint64_t const csr_rs) {
    return m_rs1;  
}

uint64_t CSRNotImm::srrs(uint64_t const csr_rs) {
    return csr_rs | m_rs1;
}

uint64_t CSRNotImm::srrc(uint64_t const csr_rs) {
    return csr_rs & (!(m_rs1));  
}

//void CSR::srrwi() {
//    m_csr_rd = 
//}

void srrsi();
void srrci();

void CSR::writeCsr(csrs_t& csrs) {
    csrs[m_index_csr] = m_csr_rd;
}

void CSR::writeBack(reg_type &reg) {
    reg[m_index_rd] = m_rd;
}

