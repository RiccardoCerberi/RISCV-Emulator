#include "DRAM.hpp"

DRAM::DRAM() {
    m_dram[ZERO] = 0;
    m_dram[SP] = DRAM_BASE + DRAM_SIZE;
}

#ifdef DEBUG
    inline void DRAM::setLastInstructionAddress(uint64_t last_instruciton_address) {
        m_last_instruction_address = last_instruciton_address; 
    }
    // to print out data formatted it should be enough the << operator
    void DRAM::printInstructionsMemory() {
        uint64_t instruction;
        uint64_t address = DRAM_BASE;
        while (address != m_last_instruction_address) {
            instruction = load_word(address, sizeof(uint32_t));
            addr
        }
    }
#endif