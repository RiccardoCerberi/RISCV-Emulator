#include "../include/memory.hpp"
#include <cstddef>

// LITTLE ENDIAN: the lew significant bit is stored in the lower address.
// Therefore 1100-0001 is stored as 0x0: 0001 0x1: 1100

SystemInterface::SystemInterface(std::string const& file_name)
    : m_last_instruction{0} {
    loadCode(file_name);
}

#ifdef DEB_BIN_INS
void SystemInterface::printCode() {
    Address_t i = krom_base;
    while (i < m_last_instruction) {
        std::cout << loadData(i, kbyte) << "\n";
        ++i;
    }
}
#endif

void SystemInterface::loadCode(std::string const& file_name) {
    std::ifstream input_file;

    input_file.open(file_name, std::ios::binary);
    assert(input_file.is_open() == true);

    Address_t is_ad = kdram_base;
    char b;
    while (input_file.read(reinterpret_cast<char*>(&b), kbyte)) {
        m_memory.write(is_ad, b, kbyte);
        is_ad += kbyte;
    }
    m_last_instruction = is_ad;
#ifdef DEBUG
    std::cout << "Last instruction: "
       << std::hex  
       << m_last_instruction
       << "\n";
#endif
#ifdef DEB_BIN_INS
    std::cout << "Code loaded: \n";
    printCode();
#endif
}

std::ostream& operator<<(std::ostream& os, std::byte b) {
    return os << std::bitset<8>(std::to_integer<int>(b));
}

static bool isAllign(Address_t ad, DataSize_t sz) { return ad % sz == 0; }

uint64_t readFromMemory(Mem_t& mem, uint64_t base, Address_t read_from,
                        DataSize_t data_size) {
    uint64_t data_to_take = 0;
    assert(read_from >= base);
    size_t const index = read_from - base;
    assert(index < mem.size());

    for (size_t i = 0; i < data_size; ++i) {
        data_to_take |= std::to_integer<decltype(data_to_take)>(mem[index + i])
                        << (8 * i);
    }
    return data_to_take;
}

bool SystemInterface::checkLimit(Address_t a) {
    return kdram_base <= a && a < (kdram_base + kdram_size);
}

void writeToMemory(Mem_t& mem, uint64_t base, Address_t where_to_write,
                   uint64_t what_to_write, DataSize_t size) {
#ifdef DEB_BIN_INS
    std::bitset<64> whs_b(what_to_write);
    std::cout << "what_to_store_binary = " << whs_b << std::endl;
#endif
    assert(where_to_write >= base);
    size_t indx = where_to_write - base;
    assert(indx < mem.size());

    for (size_t i = 0; i < size; ++i) {
        std::byte byte_to_store = std::byte(what_to_write >> (8 * i));
#ifdef DEB_BIN_INS
        std::cout << "byte_to_store = " << byte_to_store << "\n";
#endif
        mem[indx + i] = byte_to_store;
    }
}

uint64_t SystemInterface::loadData(Address_t read_from, DataSize_t sz) {
    assert(isAllign(read_from, sz));

    if (kdram_base <= read_from && read_from < (kdram_base + kdram_size)) {
        return m_memory.read(read_from, sz);
    }
#if __GNUC__ >= 13
    throw(std::format("Try to read from invalid location {}\n", read_from));
#else
    throw("Invalid read location\n");
#endif
}

void SystemInterface::storeData(Address_t write_to, uint64_t what_write,
                                DataSize_t sz) {
    assert(isAllign(write_to, sz));

    if (checkLimit(write_to)) return m_memory.write(write_to, what_write, sz);
#if __GNUC__ >= 13
    throw(std::format("Try to write {} to invalid location {}\n", what_write,
                      write_to));
#else
    throw("Invalid write location\n");
#endif
}

void DRAM::write(Address_t where_to_write, uint64_t what_to_write,
                DataSize_t size) {
    writeToMemory(m_dram, kdram_base, where_to_write, what_to_write, size);
}

uint64_t DRAM::read(Address_t read_from, DataSize_t data_size) {
    return readFromMemory(m_dram, kdram_base, read_from, data_size);
}
