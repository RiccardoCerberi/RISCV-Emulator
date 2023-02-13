#pragma once

#include"instructions.hpp"
#include <cstdint>

class Store : InstructionFormat {
public:
    Store(uint32_t const is,
          uint64_t const pc)
        : InstructionFormat(is,pc),
          m_index_base(takeBase()),
          m_index_src(takeSrc()),
          m_width(takeWidth()),
          m_imm(takeImm())
    {}
    void readRegister(reg_type const&) override;
    void execution() override;
    void accessMemory(Bus&) override;
private:

    size_t takeBase();
    size_t takeSrc();
    uint16_t takeImm();
    data_size takeWidth();

    size_t m_index_base;
    size_t m_index_src;
    uint16_t m_imm;
    data_size m_width;

    uint64_t m_base;
    uint64_t m_src;
};
