#include "../include/memory.hpp"

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
        ++i ;
    }
}
#endif

void SystemInterface::loadCode(std::string const& file_name) {
    std::ifstream input_file;

    input_file.open(file_name, std::ios::binary);
    assert(input_file.is_open() == true);

    std::vector<std::byte> code;
    std::byte b;
    while (input_file.read(reinterpret_cast<char*>(&b), kbyte)) {
        code.push_back(b);
    }
    m_last_instruction = krom_base + code.size();
#ifdef DEBUG
    std::cout << "Number of instructions: "
              << (m_last_instruction - krom_base) / 4 << "\n";
#endif
    m_rom.storeBlock(krom_base, code);
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
    size_t index = read_from - base;
    assert(index < mem.size());

    for (size_t i = 0; i < data_size; ++i) {
        data_to_take |= std::to_integer<decltype(data_to_take)>(mem[index + i])
                        << (8 * i);
    }
    return data_to_take;
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

    if (krom_base <= read_from && read_from < krom_end) {
        return m_rom.read(read_from, sz);
    }
    if (kram_base <= read_from && read_from < kram_end) {
        return m_ram.read(read_from, sz);
    }
    throw("try to read from an address out of space\n");
}

void SystemInterface::storeData(Address_t write_to, uint64_t what_write,
                                DataSize_t sz) {
    assert(isAllign(write_to, sz));

    if (kram_base <= write_to && write_to < kram_end) {
        return m_ram.write(write_to, what_write, sz);
    }
    throw("try to write from an address out of space\n");
}

void ROM::storeBlock(Address_t where_to_store,
                     std::vector<std::byte> const& what_to_load) {
    size_t i = 0;
    for (auto const& b : what_to_load) {
        writeToMemory(m_rom, krom_base, where_to_store + i,
                      std::to_integer<uint64_t>(b), kbyte);
        ++i;
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
