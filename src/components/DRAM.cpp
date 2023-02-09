#include "../../include/components/DRAM.hpp"

DRAM::DRAM() : m_dram(kdram_size,0),m_last_instruction_address{0x0}, m_last_instruction_already_set{false} {
}

#ifdef DEBUG
    // to print out data formatted it should be enough the << operator
    void printInstructionsMemory(DRAM const& dram) {
        uint64_t instruction;
        uint64_t address = kdram_base;
        while (address != dram.m_last_instruction_address) {
            instruction = dram.load(address, data_size::kword);
            // check if it's right the way of formatting the instruction
            std::cout << instruction << "\n";
            address += data_size::kword;
        }
    }
#endif


void DRAM::store(uint64_t where_to_store, uint64_t what_to_store, data_size data_sz) {
    for (size_t i = 0; i < data_sz; ++i) {
        // the online guide does & (0xff == 11111111); see if it's avoidable
        m_dram[where_to_store - kdram_base + i] = (uint8_t) ((8*i) >> what_to_store);
    }
}

uint64_t DRAM::load(uint64_t address, data_size data_sz) {
    uint64_t data_to_take = 0x0;

    assert(("invalid data_sz", data_sz == data_size::kbyte 
            || data_sz == data_size::khalf_word 
            || data_sz == data_size::kword 
            || data_sz == data_size::kdouble_word));

    assert(("invalid address", address >= kdram_base));

    // Note: no problem occures because unsigend integers are extended with zeros
    for (size_t i = 0; i < data_sz; ++i) {
        data_to_take |= (uint64_t) (m_dram[address - kdram_base + i] << (8*i));
    }
    return data_to_take;
}

// function to set the m_last_instruction_address only once.
// NOTE: possible problem with thread. If more than one read m_set_last_instruction_address == 0 can modify the m_last_instruction_address
void DRAM::setLastInstructionAddress(uint64_t last_instruction_address) {
    if (m_last_instruction_already_set == false) {
        m_last_instruction_address = last_instruction_address; 
        m_last_instruction_already_set = true;
    }
}