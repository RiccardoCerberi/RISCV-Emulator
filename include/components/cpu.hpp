#pragma once

#include <array>
#include <cstdint>
#include <bitset>
#include <cassert>
#include <iostream>
#include <fstream>
#include "constants.hpp"
#include "bus.hpp"
#include "tlb.hpp"

/*
 * TODO: configure ecall to implement system calls.
    L21 of the MIT from 6:57 there's the implemenetation
*/

// Registers cannot be pointers because they have to support all the operations like addiction or subtraction
// as well as deferencing; this will require casting, maybe I could define a function just
// for custing, maybe it would require some changes.

// NOTE: difference like t1 - t0 where the address of t1 < t0 will have strange effect
// also because they're unsigned so the subtraction will always result in a positive integers.

/*
 * cpu interacts with the memory through the bus that simply connects
 * the two entities.
 * The address provided by the cpu will be translated by the tlb, but
 * for now the tlb is limited to only return the address itself
 */
class CPU
{
public:
    // when the cpu is constructed the memory must have the instructions stored
    CPU(std::string const &);
    void steps();
    bool checkEndProgram();
#ifdef DEBUG
    void printReg();
#endif
private:
    enum opcode : uint8_t
    {
        ku = 0b0110111, // load upper immediate lui
        kauipc = 0b0010111,
        kjal = 0b1101111,
        kjalr = 0b1100111,
        kbranch = 0b1100011, 
        kload = 0b0000011,
        kstore = 0b0100011,
        kimm = 0b0010011, // operations like addi
        kop = 0b0110011,    // operations without immediate, like add
        kfence = 0b0001111,
        ksystem = 0b1110011 // ecall ect
    };

    enum funct : uint8_t {

    };
private:
    std::array<uint64_t, ktot_registers> m_registers;
    uint64_t m_pc; // it's the 32-th register
    uint64_t m_last_instr;
    Bus m_bus;
    TLB m_tlb;

    void setLastInstrAddress(uint64_t const);

    uint8_t takeBits(uint32_t, uint8_t const, uint8_t const);
    uint64_t makeImmediate(uint32_t);
    uint64_t extendSign(uint32_t);
    /*
     * 5-stages pipeline
     */
    // takes the instruction from memory at the address pointed by the pc and returns its data
    uint32_t fetch();
    // read the opcode to know which operation to perform and translates it into a number [0, 5]
    uint8_t decode(uint32_t const);
    // execute the operation decoded in the previous stage
    void execute(uint32_t const,uint8_t const);
    // memory access to store or load data
    void memoryAccess();
    // write the result to the address
    void writeBack();
};
