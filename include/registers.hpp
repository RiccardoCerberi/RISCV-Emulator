#pragma once
#include <cassert>
#include <iostream>
#include <string>

#include "constants.hpp"

class Registers {
public:
    static constexpr std::array<const char*, ktot_registers> abi_names = {
        "zero", "ra", "sp", "gp", "tp",  "t0",  "t1", "t2", "s0", "s1", "a0",
        "a1",   "a2", "a3", "a4", "a5",  "a6",  "a7", "s2", "s3", "s4", "s5",
        "s6",   "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};
    static std::string printABIName(size_t indx);

public:
    Registers() : m_registers{0} {
        m_registers[register_index::kzero_register] = 0;
        m_registers[register_index::ksp]            = kdram_base + kdram_size;
    }
    void write(size_t reg_indx, RegisterSize_t what) {
        assert(reg_indx < ktot_registers);
        if (reg_indx != register_index::kzero_register)
            m_registers[reg_indx] = what;
    }
#ifdef DEB_REGS
    void printRegs() const;
#endif
    RegisterSize_t read(size_t reg_indx) const { return m_registers[reg_indx]; }

private:
    reg_type m_registers;
};
