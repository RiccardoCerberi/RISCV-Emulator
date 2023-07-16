#pragma once
#include "instructions.hpp"

class Jis : public InstructionFormat {
    public:
        Jis(uint32_t const is, uint64_t const pc) 
            : InstructionFormat(is,pc),
              m_offset(takeOffset()),
              m_index_rd(takeIndexRd())
        {}
        void execution() override;
        void writeBack(reg_type&) override;
        uint64_t moveNextInstruction() override;
        ~Jis() = default;
    private:

        uint64_t takeOffset();
        size_t takeIndexRd();

        uint64_t m_offset;
        size_t m_index_rd;
};
