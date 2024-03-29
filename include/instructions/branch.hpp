#pragma once
#include <cstddef>
#include <cstdint>

#include "instructions.hpp"

class Branch : public InstructionFormat {
public:
    Branch(InstructionSize_t const is, Address_t const pc)
        : InstructionFormat(is, pc),
          m_index_rs1(takeRs1()),
          m_index_rs2(takeRs2()),
          m_offset(takeOffset()),
          m_func3(takeFunc3()),
          m_jump(false) {}
    void readRegister(Registers const&) override;

    void execution() override;
    Address_t moveNextInstruction() override;

private:
    enum class func3_t {
        kbeq  = 0b000,
        kbne  = 0b001,
        kblt  = 0b100,
        kbge  = 0b101,
        kbltu = 0b110,
        kbgeu = 0b111
    };

    size_t takeRs1();
    size_t takeRs2();
    Address_t takeOffset();
    func3_t takeFunc3();

    size_t m_index_rs1;
    size_t m_index_rs2;
    Address_t m_offset;
    func3_t m_func3;

    RegisterSize_t m_rs1;
    RegisterSize_t m_rs2;
    bool m_jump;

    bool beq();
    bool bne();
    bool blt();
    bool bge();
    bool bltu();
    bool bgeu();
};
