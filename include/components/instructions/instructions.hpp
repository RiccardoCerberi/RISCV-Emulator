#pragma once

#include<cstdint>
#include<iostream>
#include"../bus.hpp"
#include"../constants.hpp"
#include"../bits-manipulation.hpp"

/*
 * 
 * All opcodes
     (V) ku = 0b0110111,  // load upper immediate lui
     (V) kauipc = 0b0010111,
     (V) kjal = 0b1101111, 
     (V) kjalr = 0b1100111,
     (V) kbranch = 0b1100011,
     (V) kload = 0b0000011,
     (V) kstore = 0b0100011,
     (V) kimmop = 0b0010011,  // operations like addi
     (V) kop = 0b0110011,   // operations without immediate, like add
     (X) kfence = 0b0001111,
     ksystem = 0b1110011  // ecall ect
 *
 */

class InstructionFormat {
    public:
        InstructionFormat(uint32_t const is, uint64_t const pc)
            : m_instruction(is), m_curr_pc(pc) {}
        // it prepares the information that will use in the next stages;
        // for instance rd, rs etc
        virtual void readRegister(reg_type const&);
        virtual void readCSR(csrs_t const&);
        virtual void execution() = 0;
        virtual void accessMemory(Bus&);
        virtual void writeCsr(csrs_t&);
        virtual void writeBack(reg_type&);
        virtual uint64_t moveNextInstruction();
        virtual ~InstructionFormat() = default;
    protected:
        uint32_t const m_instruction;
        uint64_t const m_curr_pc;

#ifdef DEBUG
        virtual void printInstruction() = 0;
#endif
};









