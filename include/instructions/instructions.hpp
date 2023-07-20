#pragma once

#include<cstdint>
#include<iostream>
#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <sys/types.h>
#include"../memory.hpp"
#include"../constants.hpp"
#include"../bits-manipulation.hpp"
#include"../csr_reg.hpp"
#include"../registers.hpp"

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

RegisterSize_t arith(RegisterSize_t lhs, RegisterSize_t rhs, std::string const& op);

class InstructionFormat {
    public:
        InstructionFormat(InstructionSize_t const is, Address_t const pc)
            : m_instruction(is), m_curr_pc(pc) {}
        // it prepares the information that will use in the next stages;
        // for instance rd, rs etc
        virtual void readRegister(Registers const&);
        virtual void readCSR(CSRInterface const&);
        virtual void execution() = 0;
        virtual void accessMemory(SystemInterface&);
        virtual void writeCsr(CSRInterface&);
        virtual void writeBack(Registers&);
        virtual Address_t moveNextInstruction();
        virtual ~InstructionFormat() = default;
    protected:
        std::string printRegIndex(std::size_t); 
    protected:
        InstructionSize_t const m_instruction;
        Address_t const m_curr_pc;
};






