#include"../../include/instructions/U-format.hpp"

void Lui::execution() {
#ifdef DEBUG
    std::cout << "Lui: offset = 0x" <<std::hex<< m_offset << std::dec << std::endl;
#endif
    m_rd = m_offset;
}