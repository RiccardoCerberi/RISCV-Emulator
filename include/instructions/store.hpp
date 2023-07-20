#pragma once

#include"instructions.hpp"
#include <cstdint>

class Store : public InstructionFormat {
public:
    Store(InstructionSize_t const is,
          Address_t const pc)
        : InstructionFormat(is,pc),
          m_index_rs1(takeIndexRS1()),
          m_index_rs2(takeIndexRS2()),
          m_func3(takeFunc3()),
          m_offset(takeOffset())
    {}
    void readRegister(Registers const&) override;
    void execution() override;
    void accessMemory(SystemInterface&) override;
private:

    size_t takeIndexRS1();
    size_t takeIndexRS2();
    uint16_t takeOffset();
    uint8_t takeFunc3();

    size_t m_index_rs1;
    size_t m_index_rs2;
    uint8_t m_func3;
    RegisterSize_t m_offset;

    RegisterSize_t m_rs1;
    RegisterSize_t m_rs2;
    Address_t m_ad_write;
};
