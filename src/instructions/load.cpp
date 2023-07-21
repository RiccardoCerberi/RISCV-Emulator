#include "../../include/instructions/load.hpp"

void Load::execution() { m_ad_to_read = m_rs + m_offset; }

void Load::accessMemory(SystemInterface& bus) {
    assert(m_func3 <= 5);
    DataSize_t sz;
    if (m_func3 == 0 || m_func3 == 4) {
        sz = kbyte;
    } else if (m_func3 == 1 || m_func3 == 5) {
        sz = khalf_word;
    } else if (m_func3 == 2) {
        sz = kword;
    } else {
        std::cerr << "Invalid func3 in load instruction\n";
        abort();
    }
    m_rd = bus.readData(m_ad_to_read, sz);

    if (m_func3 <= 2) {
        m_rd = BitsManipulation::extendSign(m_rd, (1 << (m_func3 + 3)) - 1);
    }
}
