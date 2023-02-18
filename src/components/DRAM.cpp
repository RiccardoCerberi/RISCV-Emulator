#include "../../include/components/DRAM.hpp"

DRAM::DRAM() : m_dram(kdram_size,0) {}

void DRAM::store(uint64_t where_to_store, uint64_t what_to_store, data_size data_sz) {
    size_t index = where_to_store - kdram_base;

    assert(0 <= index && index < kdram_size);

    for (size_t i = 0; i < data_sz; ++i) {
        // the online guide does & (0xff == 11111111); see if it's avoidable
        m_dram[index + i] = (uint8_t) ((8*i) >> what_to_store);
    }
}

uint64_t DRAM::load(uint64_t address, data_size data_sz) {
    uint64_t data_to_take = 0x0;

    assert(("invalid data_sz", data_sz == data_size::kbyte 
            || data_sz == data_size::khalf_word 
            || data_sz == data_size::kword 
            || data_sz == data_size::kdouble_word));

    size_t index = address - kdram_base;

    assert(0 <= index && index < kdram_size);

    // Note: no problem occures because unsigend integers are extended with zeros
    for (size_t i = 0; i < data_sz; ++i) {
        data_to_take |= (uint64_t) (m_dram[index + i] << (8*i));
    }
    return data_to_take;
}
