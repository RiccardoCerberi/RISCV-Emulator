#include <cstdint>
#include <sys/types.h>

#include "../../include/components/cpu.hpp"

CPU::CPU(std::string const& file_name)
    : m_pc{kdram_base}

{
    m_registers[register_index::kzero_register] = 0;
    m_registers[register_index::ksp] = kdram_base + kdram_size;

    std::ifstream input_file;

    input_file.open(file_name, std::ios::binary);
    assert(input_file.is_open() == true);

    uint64_t adr_is = m_pc;
    uint64_t is = 0;
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

void CPU::CheckWordAllign(uint64_t const pc) {
    // the lowest two bits are not zero throw
    // the exception
// 3 = 00[...]0011
    uint64_t lowest_two_bits = 3;
    if ((pc & lowest_two_bits) != 0)
        throw "Invalid address: pc can access only word-alligned addresses";
}

#ifdef DEBUG
    uint32_t CPU::getCurrentInstruction() { return m_pc; }
#endif

bool CPU::checkEndProgram() {
    return m_pc == m_address_last_is;
}

void CPU::steps() {
    // it keeps going in the cycle till 
    // an exception occures, it might be due to pc out of boundary
    // or by the user that presses key to terminate the program
    while (checkEndProgram()) {
        uint32_t is = fetch();

        InstructionFormat* is_format = decode(is);

        execute(is_format);

        memoryAccess(is_format);

        writeBack(is_format);

        m_pc = moveNextInstruction(is_format);
        
        try {
            CheckWordAllign(m_pc);
        }
        catch(char * const txt_exception) {
            std::cout << "Exception: "  << txt_exception << std::endl;
            break;
        }
        is_format->~InstructionFormat();
    }
}

uint32_t CPU::fetch() {
    return static_cast<uint32_t>(m_bus.loadData(m_pc, data_size::kword));
}

// read the opcode to know which operation to perform and translates it into a
// number [0, 5]
InstructionFormat* CPU::decode(uint32_t const is) {
    InstructionFormat* is_format = nullptr;
    opcode_t op = opcode_t(BitsManipulation::takeBits(is, 0, 7));

    switch (op) {
        case opcode_t::klui:
            is_format = new Lui(is, m_pc);
            break;
        case opcode_t::kauipc:
            is_format = new Auipc(is, m_pc);
            break;
        case opcode_t::kjal:
            is_format = new Jis(is, m_pc);
            break;
        case opcode_t::kjalr:
            is_format = new Jris(is, m_pc);
            break;
        case opcode_t::kbranch:
            is_format = new Branch(is, m_pc);
            break;
        case opcode_t::kload:
            is_format = new Load(is, m_pc);
            break;
        case opcode_t::kstore:
            is_format = new Store(is, m_pc);
            break;
        case opcode_t::kimmop:
            is_format = new ImmOp(is, m_pc);
            break;
        case opcode_t::kop:
            is_format = new Op(is, m_pc);
            break;
        case opcode_t::kfence:
            std::cout << "fence instruction has not implemented yet\n";
            break;
        case opcode_t::ksystem: {
// speed up the code
            uint8_t func3 = BitsManipulation::takeBits(is, 12, 14);
// The inheritance works with n-level of indirection so it will work
            if (func3 == 0) {
                std::cerr << "Ecall not already defined\n";
                //is_format = new Ecall(is,m_pc);
                abort();
            }
            else
                is_format = new CSR(is, m_pc);
        }
    }
    return is_format;
}

// execute the operation decoded in the previous stage
void CPU::execute(InstructionFormat* is_format) { 
    is_format->readRegister(m_registers);
    is_format->execution(); 
}


// memory access to store or load data
void CPU::memoryAccess(InstructionFormat* is_format) {
    is_format->accessMemory(m_bus);
    is_format->writeCsr(m_csrs);
}
// write the result to the address
void CPU::writeBack(InstructionFormat* is_format) {
    is_format->writeBack(m_registers);
}

uint64_t CPU::moveNextInstruction(InstructionFormat* is_format) {
    return is_format->moveNextInstruction();
}
