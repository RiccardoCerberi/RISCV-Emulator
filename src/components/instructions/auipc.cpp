#include"../../../include/components/instructions/auipc.hpp"

void Auipc::execution() {
    m_rd = m_offset + m_curr_pc;
#ifdef DEBUG
    std::cout << "Auipc:"
              << "\n- offset(20-th) =  " << m_offset 
              << "\n- current_pc = " << m_curr_pc
              << "\nX" << m_index_rd << " = offset + current_pc = " << m_rd 
              << std::endl;
#endif
}
