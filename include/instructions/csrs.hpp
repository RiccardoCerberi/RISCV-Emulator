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
    CSR(InstructionSize_t const is, Address_t const pc);
    void readRegister(Registers const &) override;
    void readCSR(const CSRInterface &) override;
    void execution() override;
    void writeCsr(CSRInterface &) override;
    void writeBack(Registers &) override;
private:
    CSRRegisterSize_t makeCSRResult();
    bool isWriteOp();
private:
    RegisterSize_t m_second_operand;
    CSRRegisterSize_t m_csr_rs;  // alias t in riscv instructions
    CSRRegisterSize_t m_csr_rd;
    RegisterSize_t m_rd;
    bool write_to_reg;
    bool write_to_csrs;
};

