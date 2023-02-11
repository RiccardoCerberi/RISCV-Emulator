#pragma once


#include<cstdint>
#include"bus.hpp"
#include"constants.hpp"
#include"cpu.hpp"

/*
 * 
 * All opcodes
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
 *
 */

class InstructionFormat {
public:
    InstructionFormat(uint32_t const& is, uint64_t const pc)
        : m_instruction(is), m_curr_pc(pc) {}
    // it prepares the information that will use in the next stages;
    // for instance rd, rs etc
    virtual void readRegister(reg_type const&);
    virtual void execution() = 0;
    virtual void accessMemory(Bus&);
    virtual void writeBack(reg_type&);
    virtual uint64_t moveNextInstruction();
    virtual ~InstructionFormat() = default;
protected:
    uint32_t const& m_instruction;
    uint64_t const m_curr_pc;
};

class Jis : public InstructionFormat {
public:
    Jis(uint32_t const& is, uint64_t const& pc) : InstructionFormat(is,pc){}
    void execution() override;
    void writeBack(reg_type&) override;
    uint64_t moveNextInstruction() override;
    ~Jis() = default;
private:
    uint64_t m_immediate;
    size_t m_reg_save_pcis;
};

//  I-format 
//  Every I-instruction reads register and saves the result. 
//  What distinguishes any instruction is the execute function that
//  setup the result that will be stored in rd in addition to extra +
//  operation, like saving the next instruction (jalr)
class I : public InstructionFormat{
public:
    void readRegister(reg_type const&) override;
    void writeBack(reg_type&) override;
protected:
    I(uint32_t is, uint64_t const& pc) 
        : InstructionFormat(is, pc), 
          m_index_rs(takeRegS()), 
          m_index_rd(takeRegD()), 
          m_immediate(takeImm()),
          m_func3(takeFunc3())
    {}
private:
    size_t takeRegS();
    size_t takeRegD();
    uint64_t takeImm();
    uint8_t takeFunc3();
protected:
    uint64_t m_immediate;
    size_t m_index_rs;
    size_t m_index_rd;
    uint8_t m_func3;

    uint64_t m_rs;
    uint64_t m_rd;
};

class Jris : public I {
public:
    Jris(uint32_t const& is, uint64_t const&pc) : I(is,pc) {}
    void execution() override;
    uint64_t moveNextInstruction() override;
    ~Jris() = default;
private:
    uint64_t m_reg;
};

// addi, etc
class ImmOp : public I {
public:
    ImmOp(uint32_t const& is, uint64_t const&pc) : I(is,pc) {}
    void execution() override; 
private:
};




