#include"../../include/instructions/instructions.hpp"


// Default functions
void InstructionFormat::readRegister(const Registers &) {}

void InstructionFormat::readCSR(CSRInterface const&) {}

void InstructionFormat::accessMemory(SystemInterface&) {}

void InstructionFormat::writeCsr(CSRInterface&) {}

void InstructionFormat::writeBack(Registers&) {}

uint64_t InstructionFormat::moveNextInstruction() { 
    return m_curr_pc + DataSize_t::kword; 
}

std::string InstructionFormat::printRegIndex(std::size_t const reg_ind) {
    return "x" + std::to_string(reg_ind);
}

uint64_t arith(uint64_t lhs, uint64_t rhs, std::string const& op) {
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
        abort();
    }
}
