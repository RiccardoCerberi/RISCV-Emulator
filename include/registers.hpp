#pragma once 
#include"constants.hpp"
#include<cassert>

class Registers {
public:
    Registers() : m_registers{0} {
        m_registers[register_index::kzero_register] = 0;
        // this doesn't happen in real processor because it ups to the Operative
        // System to assign the sp the right value
        m_registers[register_index::ksp] = kdram_base + kdram_size;
    }
    void write(size_t reg_indx, uint64_t what) {
        assert(reg_indx < ktot_registers);
        if (reg_indx != register_index::kzero_register)
            m_registers[reg_indx] = what;
    }
#ifdef DEB_REG
    void printRegs() const {
        size_t i = 0;
        std::cout << "Registers:\n";
        for (auto const& reg : m_registers) {
            std::cout << "<\\x" << std::dec << i << "(" << printABIName(i)
                      << ") = ";
            std::cout << "0x" << std::hex << reg << "> ";
            ++i;
        }
        std::cout << std::dec << std::endl;
    }
#endif
    uint64_t read(size_t reg_indx) const { return m_registers[reg_indx]; }

private:
    reg_type m_registers;
};
