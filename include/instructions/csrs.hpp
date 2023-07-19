#pragma once

#include <cstdint>

#include "../bits-manipulation.hpp"
#include "system.hpp"

/*
 * Every instruction of this type consists in
 * - Reading value from csrs
 * - doing some operations, producing the result
 * - swapping the result with register rd
 */

class CSR : public System {
public:
    CSR(uint32_t const is, uint64_t const pc);
    void readRegister(reg_type const &) override;
    void readCSR(const CSRInterface &) override;
    void execution() override;
    void writeCsr(CSRInterface &) override;
    void writeBack(reg_type &) override;
private:
    uint64_t makeCSRResult();
    bool isWriteOp();
private:
    uint64_t m_second_operand;
    uint64_t m_csr_rs;  // alias t in riscv instructions
    uint64_t m_csr_rd;
    uint64_t m_rd;
    bool write_to_reg;
    bool write_to_csrs;
};

