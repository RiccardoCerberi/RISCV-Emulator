#include "../../include/components/cpu.hpp"
#include <cstdint>

CPU::CPU(std::string const &file_name) : m_pc{kdram_base}

{
    m_registers[register_index::kzero_register] = 0;
    m_registers[register_index::ksp] = kdram_base + kdram_size;

    std::ifstream input_file;

    input_file.open(file_name, std::ios::binary);
    assert(input_file.is_open() == true);

    uint64_t adr_is = m_pc;
    uint64_t is = 0x0;
    while (
        input_file.read(reinterpret_cast<char *>(&is), data_size::kword))
    {
        m_bus.storeData(adr_is, is, data_size::kword);
        adr_is += data_size::kword;
    }
    setLastInstrAddress(adr_is - data_size::kword);
    std::cout << "Instructions are loaded\n";
}

// I can make it inline because no other units will use that
// function
inline void CPU::setLastInstrAddress(uint64_t const l_is)
{
    m_last_instr = l_is;
}

// last is included
uint8_t CPU::takeBits(uint32_t is, uint8_t const beg,
                      uint8_t const last)
{
    assert(((last > beg) && (last - beg <= 8)));
#ifdef DEBUG
    bitset<32> ins(is);
    std::cout << "(before)instruction=" << ins << "\n";
    ins = (is >> beg) & (uint32_t(-1) >> (sizeof(is)*8 - 1 + beg - last));
    std::cout << "(after)instruction=" << ins << "\n";
#endif
// check if it's wrong
    return (is >> beg) & (uint32_t(-1) >> (sizeof(is)*8 - 1 + beg - last));
}



uint64_t CPU::makeImmediate(uint32_t seq_bit) {
    return extendSign(takeBits(seq_bit, 9, 18) |
           takeBits(seq_bit, 8,8) << 11 |
           takeBits(seq_bit, 0, 7) << 12 |
           takeBits(seq_bit, 19,19) << 20);
}

void CPU::steps()
{
    uint32_t is = fetch();
    // switching the way to see the bits based on the
    // opcode, located in the last 7 bits
    execute(is,decode(is));
    m_pc += data_size::kword;
}

uint32_t CPU::fetch()
{
return static_cast<uint32_t>(m_bus.loadData(m_pc, data_size::kword));
}

// read the opcode to know which operation to perform and translates it into a number [0, 5]
uint8_t CPU::decode(uint32_t const is)
{
return takeBits(is, 0, 7);
}

// execute the operation decoded in the previous stage
void CPU::execute(uint32_t const is, uint8_t const opcode)
{
switch (opcode) {
    case opcode::kjal:
        m_registers[takeBits(is,8, 11)] = m_pc + data_size::kword;
        uint64_t imm = makeImmediate(takeBits(is,12,31));
        // it's normally to have sum overflow, it's the way to jump backward
        m_pc += imm;
        break;
    
}
}
// memory access to store or load data
void memoryAccess();
// write the result to the address
void writeBack();
