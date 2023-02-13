#include"../../../include/components/instructions/lui.hpp"

void Lui::execution() {
    m_rd = m_offset;
}