#pragma once

#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "bus.hpp"
#include "constants.hpp"
#include "tlb.hpp"
#include "instructions/instructions.hpp"

/*
 * TODO: configure ecall to implement system calls.
    L21 of the MIT from 6:57 there's the implemenetation
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

using reg_type = std::array<uint64_t, ktot_registers>;

class InstructionFormat;

struct BitsManipulation {
    static uint32_t takeBits(uint32_t, uint8_t const, uint8_t const);
    static uint64_t extendSign(uint32_t const, uint8_t const);
};

class CPU {
public:
    // when the cpu is constructed the memory must have the instructions stored
    CPU(std::string const&);
    void steps();
    bool checkEndProgram();
#ifdef DEBUG
    void printReg();
    uint32_t getCurrentInstruction();
#endif
private:
    enum opcode : uint8_t {
        ku = 0b0110111,  // load upper immediate lui
        kauipc = 0b0010111,
        kjal = 0b1101111,
        kjalr = 0b1100111,
        kbranch = 0b1100011,
        kload = 0b0000011,
        kstore = 0b0100011,
        kimmop = 0b0010011,  // operations like addi
        kop = 0b0110011,   // operations without immediate, like add
        kfence = 0b0001111,
        ksystem = 0b1110011  // ecall ect
    };

private:
    reg_type m_registers;
    uint64_t m_pc;  // it's the 32-th register
    uint64_t m_address_last_is;
    Bus m_bus;
    TLB m_tlb;

    void setLastInstrAddress(uint64_t const);

    /*
     * 5-stages pipeline
     */
    // takes the instruction from memory at the address pointed by the pc and
    // returns its data
    uint32_t fetch();
    // reads the opcode and, based on that, creates the
    // proper instruction
    InstructionFormat* decode(uint32_t const);
    // execute the arithmetic operation decoded in the previous stage, by
    // overloading the omonimum method,
    // It's needed a registers read
    void execute(InstructionFormat*);
    // memory access to store or load data
    void memoryAccess(InstructionFormat*);
    // write the result to the address
    void writeBack(InstructionFormat*);

    uint64_t moveNextInstruction(InstructionFormat*);
};

