#include "DRAM.hpp"

DRAM::DRAM() {
    m_dram[register_index::kzero_register] = 0x0;
    m_dram[register_index::ksp] = kdram_base + kdram_size;
}

#ifdef DEBUG
    inline void DRAM::setLastInstructionAddress(uint64_t last_instruciton_address) {
        m_last_instruction_address = last_instruciton_address; 
    }
    // to print out data formatted it should be enough the << operator
    void DRAM::printInstructionsMemory() {
        uint64_t instruction;
        uint64_t address = kdram_base;
        while (address != m_last_instruction_address) {
            instruction = load_word(address, data_size::kword);
            address += data_size::kword;
        }
    }
#endif