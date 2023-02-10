#include "../../include/components/cpu.hpp"

CPU::CPU(std::string const& file_name) : m_pc{kdram_base}

{
    m_registers[register_index::kzero_register] = 0;
    m_registers[register_index::ksp] = kdram_base + kdram_size;

    std::ifstream input_file;

    input_file.open(file_name,  std::ios::binary);
    assert(input_file.is_open() == true);

    uint64_t adr_instr = m_pc;
    uint64_t instr = 0x0;
    while (
        input_file.read(reinterpret_cast<char *>(&instr), data_size::kword))
    {
        m_bus.storeData(adr_instr, instr, data_size::kword);
        adr_instr += data_size::kword;
    }
    setLastInstrAddress(adr_instr - data_size::kword);
    std::cout << "Instructions are loaded\n";
}


// I can make it inline because no other units will use that
// function
inline void CPU::setLastInstrAddress(uint64_t const last_instr) {
    m_last_instr = last_instr ;
}


uint8_t CPU::takeBits(uint32_t instr, uint8_t const beg,
 uint8_t const end) {
    assert(((end > beg) && (end-beg <= 8)));
    return beg >> ;
}

void CPU::steps() {
    uint32_t instr = fetch();
    // switching the way to see the bits based on the 
    // opcode, located in the last 7 bits
    uint8_t opcode = decode(instr);
    execute(opcode);
}




uint32_t CPU::fetch() {
    return static_cast<uint32_t>(m_bus.loadData(m_pc++, data_size::kword));
}

// read the opcode to know which operation to perform and translates it into a number [0, 5]
uint8_t CPU::decode() {

}
// execute the operation decoded in the previous stage
void execute(uint8_t const opcode) {

}
// memory access to store or load data
void memoryAccess();
// write the result to the address
void writeBack();
