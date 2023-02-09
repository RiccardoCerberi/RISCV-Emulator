#include"../../include/components/cpu.hpp"

CPU::CPU() : m_pc{kdram_base}, m_registers(ktot_registers,0) {
    m_registers[register_index::kzero_register] = 0;
    m_registers[register_index::ksp] = kdram_base + kdram_size;
}
