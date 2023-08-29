#include "memory.hpp"

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
    if (input_file.is_open() == false) {
        std::cerr << "Invalid file name: " << file_name << "\n";
        abort();
    }

    Address_t is_ad = kdram_base;
    unsigned char b;
    while (input_file.read(reinterpret_cast<char*>(&b), kbyte)) {
        m_memory.write(is_ad, b, kbyte);
        is_ad += kbyte;
    }
    m_last_instruction = is_ad;
#ifdef DEBUG
    std::cout << "Last instruction: " << std::hex << m_last_instruction
              << std::dec << std::endl;
#endif
#ifdef DEB_BIN_INS
    std::cout << "Code loaded: \n";
    printCode();
#endif
}

std::ostream& operator<<(std::ostream& os, std::byte b) {
    return os << std::bitset<8>(std::to_integer<unsigned char>(b));
}

inline bool isAlign(Address_t ad, DataSize_t sz) { return ad % sz == 0; }

inline void handleAlignmentEx() { std::cout << "Access to misaligned data\t"; }

RegisterSize_t readFromMemory(Mem_t& mem, Address_t base, Address_t read_from,
                              DataSize_t data_size) {
    RegisterSize_t data_to_take = 0;
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
    size_t indx = a - kdram_base;
    return (a >= kdram_base) && indx < kdram_size;
}

void writeToMemory(Mem_t& mem, Address_t base, Address_t where_to_write,
                   RegisterSize_t what_to_write, DataSize_t size) {
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

RegisterSize_t SystemInterface::readData(Address_t read_from, DataSize_t sz) {
    assert(checkLimit(read_from));
    if (isAlign(read_from, sz) == false) {
        handleAlignmentEx();
    }
    return m_memory.read(read_from, sz);
#if __GNUC__ >= 13
    throw(std::format("Try to read from invalid location {}\n", read_from));
#else
    throw("Invalid read location\n");
#endif
    abort();
}

bool SystemInterface::validWrite(Address_t write_to) {
    return m_last_instruction <= write_to &&
           write_to < (kdram_base + kdram_size);
}

void SystemInterface::writeData(Address_t write_to, RegisterSize_t what_write,
                                DataSize_t sz) {
    assert(checkLimit(write_to));
    if (isAlign(write_to, sz) == false) {
        handleAlignmentEx();
    }
    return m_memory.write(write_to, what_write, sz);
#if __GNUC__ >= 13
    throw(std::format("Try to write {} to invalid location {}\n", what_write,
                      write_to));
#else
    throw("Invalid write location\n");
#endif
    abort();
}

void DRAM::write(Address_t where_to_write, RegisterSize_t what_to_write,
                 DataSize_t size) {
    writeToMemory(m_dram, kdram_base, where_to_write, what_to_write, size);
}

RegisterSize_t DRAM::read(Address_t read_from, DataSize_t data_size) {
    return readFromMemory(m_dram, kdram_base, read_from, data_size);
}
