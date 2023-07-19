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
    // There are two duplicated func3 for which we need additional
    // info: the two last bits of the immediate.
    enum class func3_t : uint8_t {
        kaddi  = 0b000,
        kslli  = 0b001,
        kslti  = 0b010,
        ksltiu = 0b011,
        kxori  = 0b100,
        ksrli  = 0b101,
        ksrai  = 0b101,
        kori   = 0b110,
        kandi  = 0b111,
    };

    I(uint32_t const is, uint64_t const pc)
        : InstructionFormat(is, pc),
          m_index_rs(takeRegS()),
          m_index_rd(takeRegD()),
          m_offset(takeOffset()),
          m_func3(takeFunc3()) {}
private:
    size_t   takeRegS();
    size_t   takeRegD();
    uint64_t takeOffset();
    func3_t  takeFunc3();
protected:
    size_t   m_index_rs;
    size_t   m_index_rd;
    uint64_t m_offset;
    func3_t m_func3;

    uint64_t m_rs;
    uint64_t m_rd;
};
