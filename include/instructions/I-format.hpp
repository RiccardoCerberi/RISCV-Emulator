#pragma once

#include "instructions.hpp"

/*
 * I-format:
 * - rd => register that will store the result
 * - func3 => specifies the instruction variant (addi, slli, ...)
 * - rs1 => source register
 * - immediate
 */

class I : public InstructionFormat {
public:
    void readRegister(Registers const&) override;
    void writeBack(Registers&) override;

protected:
    I(InstructionSize_t const is, Address_t const pc)
        : InstructionFormat(is, pc),
          m_index_rs(takeRegS()),
          m_index_rd(takeRegD()),
          m_offset(takeOffset()),
          m_func3(takeFunc3()) {}

private:
    size_t         takeRegS();
    size_t         takeRegD();
    RegisterSize_t takeOffset();
    uint8_t        takeFunc3();

protected:
    size_t   m_index_rs;
    size_t   m_index_rd;
    RegisterSize_t m_offset;
    uint8_t  m_func3;

    RegisterSize_t m_rs;
    RegisterSize_t m_rd;
};
