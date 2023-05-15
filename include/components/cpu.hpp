#pragma once

#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <memory>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <sys/types.h>

#include "constants.hpp"

#include "bits-manipulation.hpp"

#include "bus.hpp"
#include "tlb.hpp"

#include "instructions/instructions.hpp"
#include "instructions/auipc.hpp"
#include "instructions/branch.hpp"
#include "instructions/imm-op.hpp"
#include "instructions/Jis.hpp"
#include "instructions/Jris.hpp"
#include "instructions/load.hpp"
#include "instructions/lui.hpp"
#include "instructions/op.hpp"
#include "instructions/store.hpp"
#include "instructions/ecall.hpp"
#include "instructions/csrs.hpp"


/*
 * TODO: configure tlb to translate addresses
 * TODO: configure ecall to implement system calls.
    L21 of the MIT from 6:57 there's the implemenetation.
    Remove DEBUG macro
*/

// Registers cannot be pointers because they have to support all the operations
// like addiction or subtraction as well as deferencing; this will require
// casting, maybe I could define a function just for custing, maybe it would
// require some changes.

// NOTE: difference like t1 - t0 where the address of t1 < t0 will have strange
// effect also because they're unsigned so the subtraction will always result in
// a positive integers.

/*
 * cpu interacts with the memory through the bus that simply connects
 * the two entities.
 * The address provided by the cpu will be translated by the tlb, but
 * for now the tlb is limited to only return the address itself
 */

class CPU {
public:
    // when the cpu is constructed the memory must have the instructions stored
    CPU(std::string const&);
    void steps();
    bool checkEndProgram();

    uint32_t getCurrentInstruction();

private:
    enum class opcode_t : uint8_t {
        klui = 0b0110111,  // load upper immediate lui
        kauipc = 0b0010111,
        kjal = 0b1101111,
        kjalr = 0b1100111,
        kbranch = 0b1100011,
        kload = 0b0000011,
        kstore = 0b0100011,
        kimmop = 0b0010011,  // operations like addi
/*
 * To invoke syscall, the user has to store the code of the syscall in a  specific register, then call syscall.
 */
        kop = 0b0110011,   // operations without immediate, like add
// fence instructions organize the sequence of instructions in a concurrent modeli (threads are called hearts), in fact, it's ensured that every instruction preceding the fence is executed before the ones after the fence. Therefore A B fence C D will be executed as {A,B} - {C,D}; the orther between instructions in curly braces can change: A-B as well as B-A.
// I'm not going to implement fence instructions at this moment, because
// it requires an advanced knowledge of concurrency.
        kfence = 0b0001111, 
        // exceptions are treated using the c++ syntax
        ksystem = 0b1110011  // ecall ect
    };


private:
    reg_type m_registers;
    uint64_t m_pc;  // it's the 32-th register
    uint64_t m_address_last_is;
    csrs_t m_csrs; // CSRs registers

    Bus m_bus;
    TLB m_tlb;

    void setLastInstrAddress(uint64_t );

    // if the pc is pointing to an address that
    // is not four byte alligned, it will throw an
    // exception
    void checkWordAlign(uint64_t pc);

    /*
     * 5-stages pipeline
     */
    // takes the instruction from memory at the address pointed by the pc and
    // returns its data
    uint32_t fetch();
    // creates the instruction based on decode bits
    std::unique_ptr<InstructionFormat> decode(uint32_t );

    void execute(std::unique_ptr<InstructionFormat> const&);
    void memoryAccess(std::unique_ptr<InstructionFormat> const&);
    void writeBack(std::unique_ptr<InstructionFormat> const&);

    uint64_t moveNextInstruction(std::unique_ptr<InstructionFormat> const&);

    void printRegs();
};
