#include"../../include/components/memory.hpp"

// LITTLE ENDIAN: the lew significant bit is stored in the lower address.
// Therefore 1100-0001 is stored as 0x0: 0001 0x1: 1100
bool ROM::storeBlock(Address_t where_to_store, std::vector<std::byte> const & what_to_load) {
    assert(what_to_load.size() <= krom_size);
#ifdef DEB_BIN_INS
    std::bitset<64> whs_b(what_to_store);
    std::cout << "what_to_store_binary = " << whs_b << std::endl;
#endif
    assert(where_to_store >= krom_base);
    size_t indx = where_to_store - krom_base;
    assert(indx < krom_size);

    for (auto const& b : what_to_load) {
        m_rom[indx++]  = b;
    }
}

uint64_t ROM::read(Address_t read_from, DataSize_t data_size) {
    uint64_t data_to_take = 0;
    assert(read_from >= krom_base);
    size_t index = read_from - krom_base;
    assert(index < krom_size);

    // TODO: end implementation
    for (size_t i = 0; i < data_size; ++i) {
        data_to_take |= (uint64_t) (m_dram[index + i] << (8 * i));
    }
    return data_to_take;: 
}
