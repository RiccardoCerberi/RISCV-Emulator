#include "../include/registers.hpp"

std::array<std::string, ktot_registers> Registers::abi_names{
    "zero", "ra", "sp", "gp", "tp",  "t0",  "t1", "t2", "s0", "s1", "a0",
    "a1",   "a2", "a3", "a4", "a5",  "a6",  "a7", "s2", "s3", "s4", "s5",
    "s6",   "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

std::string Registers::printABIName(size_t indx) {
    assert(indx < ktot_registers);
    return abi_names[indx];
}

#ifdef DEB_REG
void Registers::printRegs() const {
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