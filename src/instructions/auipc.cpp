#include"../../include/instructions/auipc.hpp"

void Auipc::execution() {
    m_rd = m_offset + m_curr_pc;
#ifdef DEBUG
    std::cout << "Auipc:"
              << " offset =  " << m_offset 
              << " current_pc = " << std::hex << m_curr_pc
              << " x" << m_index_rd << " = offset + current_pc = " << std::hex << m_rd 
              << std::dec << std::endl;
#endif
}
