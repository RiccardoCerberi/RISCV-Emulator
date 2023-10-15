#pragma once

#include <sys/types.h>

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include <cwchar>
#include <iostream>

#include "../bits-manipulation.hpp"
#include "../constants.hpp"
#include "../csr_reg.hpp"
#include "../memory.hpp"
#include "../registers.hpp"

RegisterSize_t arith(RegisterSize_t lhs, RegisterSize_t rhs,
                     std::string const& op);

class InstructionFormat {
public:
    InstructionFormat(InstructionSize_t const is, Address_t const pc)
        : m_instruction(is), m_curr_pc(pc) {}
    // it prepares the information that will use in the next stages;
    // for instance rd, rs etc
    virtual void readRegister(Registers const&);
    virtual void readCSR(CSRInterface const&);
    virtual void execution() = 0;
    virtual void accessMemory(SystemInterface&);
    virtual void writeCsr(CSRInterface&);
    virtual void writeBack(Registers&);
    virtual Address_t moveNextInstruction();
    virtual ~InstructionFormat() = default;

protected:
    std::string printRegIndex(std::size_t);

protected:
    InstructionSize_t const m_instruction;
    Address_t const m_curr_pc;
};
