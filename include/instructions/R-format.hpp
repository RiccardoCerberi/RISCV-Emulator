#pragma once

#include <sys/types.h>

#include <cstdint>

#include "instructions.hpp"

class R : public InstructionFormat {
public:
    void readRegister(Registers const&) override;
    void writeBack(Registers&) override;

protected:
    enum class id_t : uint8_t {
        kadd  = 0b00000,
        ksub  = 0b01000,
        ksll  = 0b00001,
        kslt  = 0b00010,
        ksltu = 0b00011,
        kxor  = 0b00100,
        ksrl  = 0b00101,
        ksra  = 0b01101,
        kor   = 0b110,
        kand  = 0b111,
    };
    R(InstructionSize_t const is, Address_t const pc)
        : InstructionFormat(is, pc),
          m_index_rs1(takeRegS1()),
          m_index_rs2(takeRegS2()),
          m_index_rd(takeRegD()),
          m_id(takeId()) {}

protected:
    size_t takeRegS1();
    size_t takeRegS2();
    size_t takeRegD();
    id_t takeId();

    size_t m_index_rs1;
    size_t m_index_rs2;
    size_t m_index_rd;
    id_t m_id;  // fusion of func3 and the last two bits. Not all immediate
                // instructions have this properties so for I-format has not
                // been defined.

    RegisterSize_t m_rs1;
    RegisterSize_t m_rs2;
    RegisterSize_t m_rd;
};

class Op : public R {
public:
    Op(InstructionSize_t const is, Address_t const pc) : R(is, pc) {}
    void execution() override;

private:
    void add();
    void sub();
    void sll();
    void slt();
    void sltu();
    void xorop();
    void srl();
    void sra();
    void orop();
    void andop();
    void printInstruction(std::string const& is_name, std::string const& op);
};
