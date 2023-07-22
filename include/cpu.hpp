#pragma once

#include <sys/types.h>

#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>

#include "bits-manipulation.hpp"
#include "constants.hpp"
#include "csr_reg.hpp"
#include "instructions/Jis.hpp"
#include "instructions/Jris.hpp"
#include "instructions/auipc.hpp"
#include "instructions/branch.hpp"
#include "instructions/csrs.hpp"
#include "instructions/ecall.hpp"
#include "instructions/fence.hpp"
#include "instructions/imm-op.hpp"
#include "instructions/instructions.hpp"
#include "instructions/load.hpp"
#include "instructions/lui.hpp"
#include "instructions/op.hpp"
#include "instructions/store.hpp"
#include "memory.hpp"
#include "registers.hpp"

class CPU {
public:
    CPU(std::string const&);
    void steps();
    bool checkEndProgram() { return m_pc >= m_address_last_is; }
    uint32_t getCurrentInstruction() { return m_pc; }
private:
    enum class opcode_t : uint8_t {
        klui    = 0b0110111,  // load upper immediate lui
        kauipc  = 0b0010111,
        kjal    = 0b1101111,
        kjalr   = 0b1100111,
        kbranch = 0b1100011,
        kload   = 0b0000011,
        kstore  = 0b0100011,
        kimmop  = 0b0010011,
        kop     = 0b0110011,
        kfence  = 0b0001111,
        ksystem = 0b1110011
    };

private:
    Registers m_registers;
    Address_t m_pc;
    Address_t m_address_last_is;
    CSRInterface m_csrs;
    SystemInterface m_bus;

private:
    void setLastInstrAddress(Address_t const last_ins) { m_address_last_is = last_ins; }
    /*
     * 5-stages pipeline
     */
    Address_t fetch();
    std::unique_ptr<InstructionFormat> decode(InstructionSize_t);
    void execute(std::unique_ptr<InstructionFormat> const&);
    void memoryAccess(std::unique_ptr<InstructionFormat> const&);
    void writeBack(std::unique_ptr<InstructionFormat> const&);
    InstructionSize_t moveNextInstruction(
        std::unique_ptr<InstructionFormat> const&);
};