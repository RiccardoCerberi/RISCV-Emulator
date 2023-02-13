#include"../../../include/components/instructions/auipc.hpp"

void Auipc::execution() {
    m_rd = m_offset + m_curr_pc;
}