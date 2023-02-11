#pragma once


#include<cstdint>
#include"bus.hpp"
#include"constants.hpp"


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
        kimm = 0b0010011,  // operations like addi
        kop = 0b0110011,   // operations without immediate, like add
        kfence = 0b0001111,
        ksystem = 0b1110011  // ecall ect
 *
 */

class InstructionFormat {
public:
    InstructionFormat(uint32_t const&);
    // it prepares the information that will use in the next stages;
    // for instance rd, rs etc
    virtual void execution() = 0;
    // by default instructions that don't access memory or registers do nothing
    virtual void accessMemory(Bus&);
    virtual void writeBack(reg_type&);
    virtual void moveNextInstruction(uint64_t&);
    virtual ~InstructionFormat() = default;
protected:
    uint32_t const& m_instruction;
};

class Jis : public InstructionFormat {
public:
    Jis(uint32_t const& is) : InstructionFormat(is) {}
    void execution() override;
    void writeBack(reg_type&) override;
    void moveNextInstruction(uint64_t&) override;
    ~Jis() = default;
private:
    uint64_t m_immediate;
    size_t m_reg_save_pcis;
};

//  I-format 
class I : public InstructionFormat{
protected:
    I(uint32_t is) 
        : InstructionFormat(is), m_reg_src(takeRegS()), m_reg_dest(takeRegD()), m_immediate(takeImm())
    {}
private:
    size_t takeRegS();
    size_t takeRegD();
    uint64_t takeImm();
protected:
    uint64_t m_immediate;
    size_t m_reg_src;
    size_t m_reg_dest;
};

class Jris : public I {
public:
    Jris(uint32_t const& is) : I(is) {}
    void execution() override;
    void writeBack(reg_type&) override;
    void moveNextInstruction(uint64_t&) override;
    ~Jris() = default;
private:
};
