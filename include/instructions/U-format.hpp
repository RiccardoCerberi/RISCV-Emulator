#pragma once 

#include"instructions.hpp"
#include <cstdint>

/*
    U-type:
    - rd => register to store the result
    - immediate

    When we want to load a constant to a register, we use
     pseudo instructions like li; these instructions split
     the 32 bits constant in two parts: the first 12 bits and the last 20.
     The U-type instructions load the 20 most significant bits, the remaining
     bits are loaded by I-type operations, like addi
*/

class U : public InstructionFormat {
    public:
        U(InstructionSize_t const is, Address_t const pc) 
        : InstructionFormat(is,pc),
          m_offset(takeOffset()),
          m_index_rd(takeRd())
    {}
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
    Auipc(InstructionSize_t const is, Address_t const pc)
        : U(is, pc)
    {}
    void execution() override;
};


class Lui : public U {
public:
    Lui(InstructionSize_t const is, Address_t const pc)
     : U(is, pc)
    {}
    void execution() override;
};