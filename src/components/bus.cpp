#include "../../include/components/bus.hpp"

#ifdef DEBUG
void Bus::printMemory(uint64_t const beg_adr, uint64_t const end_adr, data_size const& data_sz)
{
    uint64_t data;
    uint64_t adr = beg_adr;
    while (adr != end_adr)
    {
        data = load(adr, data_sz);
        std::cout << data << "\n";
        adr += data_sz::kword;
    }
}
#endif