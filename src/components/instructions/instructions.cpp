#include"../../include/components/instructions/instructions.hpp"
#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <sys/types.h>

// Default functions

void InstructionFormat::readRegister(const reg_type &) {}

void InstructionFormat::accessMemory(Bus&) {}

void InstructionFormat::writeBack(reg_type&) {}

uint64_t InstructionFormat::moveNextInstruction() { 
    return m_curr_pc + data_size::kword; 
}



