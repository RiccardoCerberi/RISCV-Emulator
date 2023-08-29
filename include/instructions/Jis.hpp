#pragma once
#include "instructions.hpp"

class Jis : public InstructionFormat {
public:
    Jis(InstructionSize_t const is, Address_t const pc)
        : InstructionFormat(is, pc),
          m_offset(takeOffset()),
          m_index_rd(takeIndexRd()) {}
    void execution() override;
    void writeBack(Registers&) override;
    Address_t moveNextInstruction() override;
    ~Jis() = default;

private:
    Address_t takeOffset();
    size_t takeIndexRd();

    Address_t m_offset;
    size_t m_index_rd;
};
