#pragma once

#include <cstdint>

#include "instructions.hpp"

class U : public InstructionFormat {
public:
    U(InstructionSize_t const is, Address_t const pc)
        : InstructionFormat(is, pc),
          m_index_rd(takeRd()),
          m_offset(takeOffset()) {}
    void writeBack(Registers&) override;

protected:
    RegisterSize_t takeOffset();
    size_t takeRd();

    size_t m_index_rd;
    RegisterSize_t m_offset;
    RegisterSize_t m_rd;
};

class Auipc : public U {
public:
    Auipc(InstructionSize_t const is, Address_t const pc) : U(is, pc) {}
    void execution() override;
};

class Lui : public U {
public:
    Lui(InstructionSize_t const is, Address_t const pc) : U(is, pc) {}
    void execution() override;
};
