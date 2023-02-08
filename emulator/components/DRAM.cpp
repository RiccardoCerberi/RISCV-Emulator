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
            instruction = load(address, data_size::kword);
            address += data_size::kword;
        }
    }
#endif


void DRAM::store(uint64_t where_to_store, uint64_t what_to_store, data_size data_sz) {
    
}

uint64_t DRAM::load(uint64_t address, data_size data_sz) {
    uint64_t data_to_take = 0x0;

    assert(("invalid data_sz", data_sz == data_size::kbyte 
            || data_sz == data_size::khalf_word 
            || data_sz == data_size::kword 
            || data_sz == data_size::kdouble_word));

    assert(("invalid address", address >= kdram_base));

    // Note: no problem occures because unsigend integers are extended with zeros
    for (int i = 0; i < data_sz; ++i) {
        data_to_take |= (uint64_t) (m_dram[address - kdram_base + i] << (8*i));
    }
    return data_to_take;
}

