#include"../../include/instructions/load.hpp"


void Load::execution() {
    m_rs = m_rs + m_offset;
}

// TODO: check correctness 
void Load::accessMemory(SystemInterface& bus) {
    m_rd = bus.loadData(m_rs, static_cast<DataSize_t>(m_id));
}
