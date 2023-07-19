#include "../include/cpu.hpp"

CPU::CPU(std::string const& file_name) : m_pc{kdram_base}, m_bus{file_name} {
    m_address_last_is = m_bus.getLastInstruction();
    m_registers[register_index::kzero_register] = 0;
    // this doesn't happen in real processor because it ups to the Operative System to assign the sp the right value
    m_registers[register_index::ksp] = kdram_base + kdram_size;
}

inline void CPU::setLastInstrAddress(uint64_t const l_is) {
    m_address_last_is = l_is;
}

uint32_t CPU::getCurrentInstruction() { return m_pc; }

static std::string abi_names[ktot_registers] = {
    "zero",
    "ra",
    "sp",
    "gp",
    "tp",
    "t0",
    "t1",
    "t2",
    "s0",
    "s1",
    "a0", "a1","a2", "a3", "a4", "a5", "a6", "a7",
    "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11",
    "t3", "t4", "t5", "t6"
};

std::string printABIName(size_t indx) {
    assert(indx < ktot_registers);
    return abi_names[indx];
}


void CPU::printRegs() {
    size_t i = 0;

    std::cout << "Registers:\n";
    for (auto const& reg : m_registers) {
        std::cout << "<\\x" << std::dec << i << "(" << printABIName(i) << ") = ";
        std::cout << "0x" << std::hex << reg << "> ";
        ++i;
    }
    std::cout << std::endl;
}

// The processor performs one operation per clock cycle (is not how modern processor works) this make the design easier, avoiding conflicts 
// with jump instructions.
// Instructions are divided in classes based on the instruction format on riscv manual
bool CPU::checkEndProgram() { return m_pc == m_address_last_is; }
void CPU::steps() {
    while (!checkEndProgram()) {
        uint32_t is = fetch();
#ifdef DEB_PC
        std::cout << "pc = " << std::hex << m_pc << " "
                  << "instruction = " << std::bitset<32>(is) << std::endl;
#endif
#ifdef DEB_REGS
        printRegs();
#endif
        std::unique_ptr<InstructionFormat> is_format = nullptr;
        try {
            is_format = decode(is);
        } catch (const char* decode_exc) {
            std::cout << "Exception in decoding instruction: " << decode_exc
                      << "\n";
            break;
        }

        assert(is_format != nullptr);

        try {
            execute(is_format);
        } catch (const char* execute_exc) {
            std::cout << "Exception in excuting instruction: " << execute_exc
                      << std::endl;
#ifdef DEBUG
            abort();
#endif
            break;
        }
        memoryAccess(is_format);

        writeBack(is_format);
        try {
            m_pc = moveNextInstruction(is_format);
        } catch (char* const txt_exception) {
            std::cout << "Exception: " << txt_exception << std::endl;
            break;
        }
        m_csrs.updateTimer();
    }
}

uint32_t CPU::fetch() {
    return static_cast<uint32_t>(m_bus.loadData(m_pc, DataSize_t::kword));
}

// decode function uses polymorphism, in order to know which instruction return
// it needs to decode the first 8 bits.
std::unique_ptr<InstructionFormat> CPU::decode(uint32_t const is) {
    std::unique_ptr<InstructionFormat> is_format;
#ifdef DEBUG
    uint8_t opcode = BitsManipulation::takeBits(is, 0, klast_opcode_digit);
    std::cout << "<opcode = " << std::bitset<8>(opcode) << "> ";
#endif

    auto op = opcode_t(static_cast<uint8_t>(
        BitsManipulation::takeBits(is, 0, klast_opcode_digit)));
    switch (op) {
        case opcode_t::klui:
            is_format = std::make_unique<Lui>(is, m_pc);
            break;
        case opcode_t::kauipc:
            is_format = std::make_unique<Auipc>(is, m_pc);
            break;
        case opcode_t::kjal:
            is_format = std::make_unique<Jis>(is, m_pc);
            break;
        case opcode_t::kjalr:
            is_format = std::make_unique<Jris>(is, m_pc);
            break;
        case opcode_t::kbranch:
            is_format = std::make_unique<Branch>(is, m_pc);
            break;
        case opcode_t::kload:
            is_format = std::make_unique<Load>(is, m_pc);
            break;
        case opcode_t::kstore:
            is_format = std::make_unique<Store>(is, m_pc);
            break;
        case opcode_t::kimmop:
            is_format = std::make_unique<ImmOp>(is, m_pc);
            break;
        case opcode_t::kop:
            is_format = std::make_unique<Op>(is, m_pc);
            break;
        case opcode_t::kfence:
            std::cout << "fence instruction has not been implemented yet\n";
            break;
        case opcode_t::ksystem: {
            uint8_t func3 = BitsManipulation::takeBits(is, 12, 14);
            if (func3 == 0) {
                std::cerr << "Ecall not already defined\n";
                abort();
            } else
                is_format = std::make_unique<CSR>(is, m_pc);
            break;
        }
        default:
            throw "Invalid opcode";
    }
    return is_format;
}

void CPU::execute(std::unique_ptr<InstructionFormat> const& is_format) {
    is_format->readRegister(m_registers);
    is_format->readCSR(m_csrs);
    try {
        is_format->execution();
    } catch (const char* exc) {
        throw exc;
    }
}

void CPU::memoryAccess(std::unique_ptr<InstructionFormat> const& is_format) {
    is_format->accessMemory(m_bus);
    is_format->writeCsr(m_csrs);
}

void CPU::writeBack(std::unique_ptr<InstructionFormat> const& is_format) {
    is_format->writeBack(m_registers);
}

uint64_t CPU::moveNextInstruction(
    std::unique_ptr<InstructionFormat> const& is_format) {
    return is_format->moveNextInstruction();
}
