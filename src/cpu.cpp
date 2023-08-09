#include "../include/cpu.hpp"

CPU::CPU(std::string const& file_name) : m_pc{kdram_base}, m_bus{file_name} {
    m_address_last_is = m_bus.getLastInstruction();
}

void CPU::steps() {
    while (!checkEndProgram()) {
        uint32_t is = fetch();
#ifdef DEBUG
        std::cout << "<current_instruction> pc = " << std::hex << m_pc
                  << std::dec << std::endl;
#endif
#ifdef DEB_REGS
        m_registers.printRegs();
#endif
        std::unique_ptr<InstructionFormat> is_format = nullptr;
        try {
            is_format = decode(is);
        } catch (const char* dec_exc) {
            std::cout << "Exception in decoding stage: " << dec_exc
                      << "\n";
            break;
        }
        assert(is_format != nullptr);

        try {
            execute(is_format);
        } catch (const char* exec_exc) {
            std::cout << "Exception in execute stage: " << exec_exc
                      << std::endl;
            break;
        }

        try {
            memoryAccess(is_format);
        } catch (const char* mem_exc) {
            std::cout << "Exception in memory stage: " << mem_exc << std::endl;
            break;
        }

        writeBack(is_format);
        try {
            m_pc = moveNextInstruction(is_format);
        } catch (char* const wb_exception) {
            std::cout << "Exception in write back stage: " << wb_exception << std::endl;
            break;
        }
        m_csrs.updateTimer();
    }
}

// pipeline stages
Address_t CPU::fetch() { return m_bus.readData(m_pc, DataSize_t::kword); }

// decode function uses polymorphism, in order to know which instruction return
// it needs to decode the first 8 bits.
std::unique_ptr<InstructionFormat> CPU::decode(InstructionSize_t const is) {
    std::unique_ptr<InstructionFormat> is_format = nullptr;
#ifdef DEBUG
    uint8_t opcode = BitsManipulation::takeBits(is, 0, klast_opcode_digit);
    std::cout << "<opcode = " << std::bitset<kopcode_len>(opcode) << "> ";
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
            is_format = std::make_unique<Fence>(is, m_pc);
            break;
        case opcode_t::ksystem: {
            uint8_t func3 = BitsManipulation::takeBits(is, 12, 14);
            if (func3 == 0) {
                is_format = std::make_unique<Ecall>(is, m_pc);
            } else
                is_format = std::make_unique<CSR>(is, m_pc);
            break;
        }
        default: {
            std::cerr << "No opcode matches\n";
            abort();
        }
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

InstructionSize_t CPU::moveNextInstruction(
    std::unique_ptr<InstructionFormat> const& is_format) {
    return is_format->moveNextInstruction();
}
