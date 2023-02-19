#include"../../../include/components/instructions/auipc.hpp"

void Auipc::execution() {
#ifdef DEBUG
    std::cout << "Add immediate respect to pc\n";
#endif
    m_rd = m_offset + m_curr_pc;
}
