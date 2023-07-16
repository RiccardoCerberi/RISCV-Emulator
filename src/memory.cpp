#include "../include/memory.hpp"

// LITTLE ENDIAN: the lew significant bit is stored in the lower address.
// Therefore 1100-0001 is stored as 0x0: 0001 0x1: 1100
SystemInterface::SystemInterface(std::string const& file_name) {
    std::ifstream input_file;

    input_file.open(file_name, std::ios::binary);
    assert(input_file.is_open() == true);

    Mem_t code;
    std::byte b;
    while (input_file.read(reinterpret_cast<char *>(&b), kbyte)) {
        code.push_back(b);
    }
    m_rom.storeBlock(krom_base, code);
}

static bool isAllign(Address_t ad, DataSize_t sz) {
    return ad % sz == 0;
}

uint64_t readFromMemory(Mem_t& mem, uint64_t base, Address_t read_from, DataSize_t data_size)  {
    uint64_t data_to_take = 0;
    assert(read_from >= base);
    size_t index = read_from - base;
    assert(index < mem.size());

    for (size_t i = 0; i < data_size; ++i) {
        data_to_take |= std::to_integer<decltype(data_to_take)>(mem[index + i] << (8 * i));
    }
    return data_to_take;
}

void writeToMemory(Mem_t& mem,uint64_t base, Address_t where_to_write, uint64_t what_to_write, DataSize_t size) {
#ifdef DEB_BIN_INS
    std::bitset<64> whs_b(what_to_store);
    std::cout << "what_to_store_binary = " << whs_b << std::endl;
#endif
    assert(where_to_write >= base);
    size_t indx = where_to_write - base;
    assert(indx < mem.size());


    for (size_t i = 0; i < size; ++i) {
        std::byte byte_to_store = std::byte(what_to_write >> (8 * i));
#ifdef DEB_BIN_INS
        std::cout << "byte_to_store = " << std::bitset<8>(byte_to_store)
                  << "\n";
#endif
        mem[indx + i] = byte_to_store;
    }

}

uint64_t SystemInterface::loadData(Address_t read_from, DataSize_t sz) {
    assert(isAllign(read_from, sz));

    if (krom_base <= read_from && read_from < krom_end) {
        return m_rom.read(read_from, sz);
    }
    if (kram_base <= read_from && read_from < kram_end) {
        return m_ram.read(read_from, sz);
    }
    throw("try to read from an address out of space\n");
}

void SystemInterface::storeData(Address_t write_to, uint64_t what_write, DataSize_t sz) {
    assert(isAllign(write_to, sz));

    if (kram_base <= write_to && write_to < kram_end) {
        return m_ram.write(write_to, what_write, sz);
    }
    throw("try to write from an address out of space\n");
}

void ROM::storeBlock(Address_t where_to_store,
                     std::vector<std::byte> const &what_to_load) {
    size_t i = 0;
    for (auto const &b : what_to_load) {
        writeToMemory(m_rom, krom_base, where_to_store + 8*i, std::to_integer<uint64_t>(b), kbyte);
    }
}

uint64_t ROM::read(Address_t read_from, DataSize_t data_size) {
    return readFromMemory(m_rom, krom_base, read_from, data_size);
}

void RAM::write(Address_t where_to_write, uint64_t what_to_write,
                DataSize_t size) {
    writeToMemory(m_ram, kram_base, where_to_write, what_to_write, size);
}

uint64_t RAM::read(Address_t read_from, DataSize_t data_size) {
    return readFromMemory(m_ram, kram_base, read_from, data_size);
}
