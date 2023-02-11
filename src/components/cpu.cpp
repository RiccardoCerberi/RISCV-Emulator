#include "../../include/components/cpu.hpp"

#include <cstdint>
#include <sys/types.h>

CPU::CPU(std::string const& file_name)
    : m_pc{kdram_base}

{
    m_registers[register_index::kzero_register] = 0;
    m_registers[register_index::ksp] = kdram_base + kdram_size;

    std::ifstream input_file;

    input_file.open(file_name, std::ios::binary);
    assert(input_file.is_open() == true);

    uint64_t adr_is = m_pc;
    uint64_t is = 0x0;
    while (input_file.read(reinterpret_cast<char*>(&is), data_size::kword)) {
        m_bus.storeData(adr_is, is, data_size::kword);
        adr_is += data_size::kword;
    }
    setLastInstrAddress(adr_is - data_size::kword);
    std::cout << "Instructions are loaded\n";
}

// I can make it inline because no other units will use that
// function
inline void CPU::setLastInstrAddress(uint64_t const l_is) {
    m_address_last_is = l_is;
}

// last is included
uint8_t BitsManipulation::takeBits(uint32_t is, uint8_t const beg, uint8_t const last) {
    assert(((last > beg) && (last - beg <= 8)));
#ifdef DEBUG
    bitset<32> ins(is);
    std::cout << "(before)instruction=" << ins << "\n";
    ins = (is >> beg) & (uint32_t(-1) >> (sizeof(is) * 8 - 1 + beg - last));
    std::cout << "(after)instruction=" << ins << "\n";
#endif
    // check if it's wrong
    return (is >> beg) & (uint32_t(-1) >> (sizeof(is) * 8 - 1 + beg - last));
}

void CPU::steps() {
    uint32_t is = fetch();

    InstructionFormat* is_format = decode(is);

    execute(is_format);

    memoryAccess(is_format);

    writeBack(is_format);

    is_format->~InstructionFormat();

    m_pc += data_size::kword;
}

uint32_t CPU::fetch() {
    return static_cast<uint32_t>(m_bus.loadData(m_pc, data_size::kword));
}

// read the opcode to know which operation to perform and translates it into a
// number [0, 5]
InstructionFormat* CPU::decode(uint32_t const is) {
    InstructionFormat* is_format = nullptr;

    switch (BitsManipulation::takeBits(is, 0, 7)) {
        case kjal:
            is_format = new Jis(is);
            // TODO: complete all cases
        case kjalr:
            is_format = new Jris(is);
    }
    return is_format;
}

// execute the operation decoded in the previous stage
void CPU::execute(InstructionFormat* is_format) { is_format->execution(); }
// memory access to store or load data
void CPU::memoryAccess(InstructionFormat* is_format) {
    is_format->accessMemory(m_bus);
}
// write the result to the address
void CPU::writeBack(InstructionFormat* is_format) {
    is_format->writeBack(m_registers, m_pc);
}

