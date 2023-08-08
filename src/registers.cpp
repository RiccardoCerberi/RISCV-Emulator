#include "../include/registers.hpp"

std::string Registers::printABIName(size_t indx) {
    assert(indx < ktot_registers);
    return abi_names[indx];
}

#ifdef DEB_REGS
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
