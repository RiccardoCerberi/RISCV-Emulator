#pragma once
#include <cassert>
#include <string>

#include "constants.hpp"

class Registers {
public:
    static std::array<std::string, ktot_registers> abi_names;
    static std::string                             printABIName(size_t indx);

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
#ifdef DEB_REG
    void printRegs();
#endif
    RegisterSize_t read(size_t reg_indx) const { return m_registers[reg_indx]; }

private:
    reg_type m_registers;
};
