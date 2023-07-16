#include "../../include/components/bus.hpp"

void Bus::printMemory(uint64_t const beg_adr, uint64_t const end_adr, data_size const& data_sz)
{
    uint64_t data;
    uint64_t adr = beg_adr;
    while (adr != end_adr)
    {
        data = loadData(adr, data_sz);
        std::cout << data << "\n";
        adr += data_size::kword;
    }
}

uint64_t Bus::loadData(uint64_t const address, data_size const& data_sz) {
    return m_dram.load(address, data_sz);
}


void Bus::storeData(uint64_t const where, uint64_t const src, data_size const& data_sz) {
    m_dram.store(where, src, data_sz);
}
