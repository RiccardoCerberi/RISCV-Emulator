#pragma once

#include"system.hpp"
#include <cstdint>

/*
 * Every instruction of this type consists in 
 * - Reading value from csrs
 * - doing some operations, producing the result
 * - swapping the result with register rd
 */

class CSR : public System {
public:
    CSR(uint32_t const is, uint64_t const pc)
        : System(is,pc), m_index_csr(m_func12)
    {}
    void readRegister(reg_type const&) override;
    void readCSR(const csrs_t &) override;
    void execution() override;
    void accessCsr(csrs_t& csrs) override;
    void writeBack(reg_type &) override;
private:
// TODO: implement csr functions
    void srrw();
    void srrs();
    void srrc();
    void srrwi();
    void srrsi();
    void srrci();
private:
    uint16_t const& m_index_csr;
    uint64_t m_rs1;
    uint64_t m_csr_rs; // alias t in riscv instructions
    uint64_t m_csr_rd;
    uint64_t m_rd;
}; 
