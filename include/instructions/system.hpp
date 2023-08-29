#pragma once

#include <cstdint>
#include <memory>

#include "bits-manipulation.hpp"
#include "instructions.hpp"

class System : public InstructionFormat {
public:
    System(InstructionSize_t const is, Address_t const pc)
        : InstructionFormat(is, pc),
          m_index_rd(takeRd()),
          m_qty(takeQty()),
          m_func3(takeFunc3()),
          m_func12(takeFunc12()) {}
    enum class func3_t : uint8_t {
        kecall  = 0b000,
        kebreak = 0b000,
        kcsrrw  = 0b001,
        kcsrrs  = 0b010,
        ksrrc   = 0b011,
        kcsrrwi = 0b101,
        ksrrsi  = 0b110,
        kcsrrci = 0b111
    };

private:
    size_t takeRd();
    uint8_t takeQty();
    func3_t takeFunc3();
    uint16_t takeFunc12();

protected:
    size_t m_index_rd;
    uint8_t m_qty;  // to distinguish from immediate and normal csrs opearation
    func3_t m_func3;
    uint16_t m_func12;
};

// Ecall differs from Ebreak for the func12 bits
class Ecall : public System {
public:
    Ecall(InstructionSize_t const is, Address_t const pc) : System(is, pc) {}
    void execution() override { std::cout << "Calling to operative system\n"; }
};

class CSR : public System {
public:
    CSR(InstructionSize_t const is, Address_t const pc);
    void readRegister(Registers const &) override;
    void readCSR(const CSRInterface &) override;
    void execution() override;
    void writeCsr(CSRInterface &) override;
    void writeBack(Registers &) override;

private:
    CSRRegisterSize_t makeCSRResult();
    bool isWriteOp();

private:
    RegisterSize_t m_second_operand;
    CSRRegisterSize_t m_csr_rs;  // alias t in riscv manual
    CSRRegisterSize_t m_csr_rd;
    RegisterSize_t m_rd;
    bool write_to_reg;
    bool write_to_csrs;
};
