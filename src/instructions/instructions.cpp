#include"../../../include/components/instructions/instructions.hpp"
#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <sys/types.h>

// Default functions
void InstructionFormat::readRegister(const reg_type &) {}

void InstructionFormat::readCSR(csrs_t const&) {}

void InstructionFormat::accessMemory(Bus&) {}

void InstructionFormat::writeCsr(csrs_t&) {}

void InstructionFormat::writeBack(reg_type&) {}

uint64_t InstructionFormat::moveNextInstruction() { 
    return m_curr_pc + data_size::kword; 
}


std::string InstructionFormat::printRegIndex(std::size_t const reg_ind) {
    return "x" + std::to_string(reg_ind);
}

uint64_t arith(uint64_t lhs, uint64_t rhs, std::string const& op) {
    uint64_t res;
    if (op == "+") {
        return  lhs + rhs;
    } else if (op == "-") {
        return lhs - rhs;
    } else if (op == "<<"){
        return lhs << rhs;
    } else if (op == ">>") {
        return lhs >> rhs;
    } else if (op == "^") {
        return lhs ^ rhs;
    } else if (op == "|") {
        return lhs | rhs;
    } else if (op == "&") {
        return lhs & rhs;
    } else {
        std::cerr << "Error: operator " << op << " doesn't match\n";
    }
}
