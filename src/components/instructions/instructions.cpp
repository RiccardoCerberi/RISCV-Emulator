#include"../../include/components/instructions/instructions.hpp"
#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <sys/types.h>

// Default functions

void InstructionFormat::readRegister(const reg_type &) {}

void InstructionFormat::readCSR(csrs_t const&) {}

void InstructionFormat::accessMemory(Bus&) {}

void InstructionsFormat::accessCsrs(csrs_t&) {}

void InstructionFormat::writeBack(reg_type&) {}

uint64_t InstructionFormat::moveNextInstruction() { 
    return m_curr_pc + data_size::kword; 
}
