#include"../../include/components/load.hpp"


void Load::execution() {
    m_rs = m_rs + m_immediate;
}

void Load::accessMemory(Bus& bus) {
    // TODO: check if it's valid case
    m_rd = bus.loadData(m_rs, static_cast<data_size>(m_func3));
}
