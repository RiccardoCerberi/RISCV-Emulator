#include "../../include/components/DRAM.hpp"

DRAM::DRAM() : m_dram(kdram_size, 0) {}

void DRAM::store(uint64_t where_to_store, uint64_t what_to_store, data_size data_sz) {
    size_t index = where_to_store - kdram_base;

    assert(0 <= index && index < kdram_size);
#ifdef DEBUG
    std::bitset<64> whs_b(what_to_store);
    std::cout << "what_to_store_binary = " << whs_b << std::endl;
#endif

    for (size_t i = 0; i < data_sz; ++i) {
        auto byte_to_store = static_cast<uint8_t>(what_to_store >> (8*i));
#ifdef DEBUG
        std::cout << "byte_to_store = " << std::bitset<8>(byte_to_store) << "\n";
#endif
        m_dram[index + i] = byte_to_store;
    }
}

uint64_t DRAM::load(uint64_t address, data_size data_sz) {
    uint64_t data_to_take = 0;

    assert(("invalid data_sz", data_sz == data_size::kbyte
                               || data_sz == data_size::khalf_word
                               || data_sz == data_size::kword
                               || data_sz == data_size::kdouble_word));

    size_t index = address - kdram_base;

    assert(0 <= index && index < kdram_size);

    for (size_t i = 0; i < data_sz; ++i) {
        data_to_take |= (uint64_t) (m_dram[index + i] << (8 * i));
    }
    return data_to_take;
}
