#include"../../include/instructions/lui.hpp"

void Lui::execution() {
#ifdef DEBUG
    std::cout << "Lui(20-th bit):\n offset = " << m_offset << std::endl;
#endif
    m_rd = m_offset;
}