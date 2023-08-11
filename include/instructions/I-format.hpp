#pragma once
#include "instructions.hpp"

class I : public InstructionFormat {
public:
    void readRegister(Registers const &) override;
    void writeBack(Registers &) override;

protected:
    I(InstructionSize_t const is, Address_t const pc)
        : InstructionFormat(is, pc),
          m_index_rs(takeRegS()),
          m_index_rd(takeRegD()),
          m_offset(takeOffset()),
          m_func3(takeFunc3()) {}

private:
    size_t takeRegS();
    size_t takeRegD();
    RegisterSize_t takeOffset();
    uint8_t takeFunc3();

protected:
    size_t m_index_rs;
    size_t m_index_rd;
    RegisterSize_t m_offset;
    uint8_t m_func3;

    RegisterSize_t m_rs;
    RegisterSize_t m_rd;
};

class ImmOp : public I {
private:
    // There are two duplicated func3 for which we need additional
    // info: the two last bits of the immediate.
    enum class func3_t : uint8_t {
        kaddi  = 0b000,
        kslli  = 0b001,
        kslti  = 0b010,
        ksltiu = 0b011,
        kxori  = 0b100,
        ksrli  = 0b101,
        ksrai  = 0b101,
        kori   = 0b110,
        kandi  = 0b111,
    };

public:
    ImmOp(InstructionSize_t const is, Address_t const pc)
        : I(is, pc), m_func3{I::m_func3} {}
    void execution() override;

private:
    void addi();
    void slti();
    void sltiu();
    void xori();
    void ori();
    void andi();
    void slli();
    void srli();
    void srai();
    void printInstruction(std::string const &is_name, std::string const &op);
    func3_t m_func3;
};

class Jris : public I {
public:
    Jris(InstructionSize_t const is, Address_t const pc) : I(is, pc) {}
    void execution() override;
    Address_t moveNextInstruction() override;
    ~Jris() = default;

private:
    RegisterSize_t m_reg;
};

class Load : public I {
public:
    Load(InstructionSize_t const is, Address_t const pc) : I(is, pc) {}
    void execution() override;
    void accessMemory(SystemInterface &) override;

private:
    Address_t m_ad_to_read;
};
