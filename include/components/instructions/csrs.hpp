#pragma once

#include"system.hpp"
#include <cstdint>

/*
 * Every instruction of this type consists in 
 * - Reading value from csrs
 * - doing some operations, producing the result
 * - swapping the result with register rd
 */

/*
 * CSR class can be split in two parts: csr_notimm and csr_imm; 
 * the difference between these two types is the interpretation of bits from 15-19.
 * Csr_notimm uses these bits to read data from the registers, when csr_imm use it as 
 * immediate.
 * For this reason, the execution function that produces the result that will be written to CSR is different.
 * Therefore I need to define a class that represents these problems
 */

class CSRAux {
protected:
    using func3_t = System::func3_t;
public:
    CSRAux(System::func3_t const func3, uint8_t const qty) 
        : m_func3(func3), m_qty(qty)
    {}
// It might be  either a register reading or making the immediate
    virtual void InterpretQty(reg_type const&) {}
    virtual uint64_t makeCSRResult(uint64_t const) = 0;
protected:
    func3_t m_func3;
    uint8_t m_qty;
    uint64_t m_rs1; // it can be either index in reg or immediate
};

class CSRNotImm : public CSRAux {
public: 
    CSRNotImm(func3_t const func3, uint8_t const qty) 
        : CSRAux(func3, qty)
    {}
     void InterpretQty(reg_type const&) override;
     uint64_t makeCSRResult(uint64_t const) override;
private:
    uint64_t srrw(uint64_t const);
    uint64_t srrs(uint64_t const);
    uint64_t srrc(uint64_t const);
};

class CSRImm : public CSRAux {
public: 
    CSRImm(func3_t const func3, uint8_t const qty) 
        : CSRAux(func3,qty)
    {}
     void InterpretQty(reg_type const&) override;
     uint64_t makeCSRResult(uint64_t const) override;
private:
    void srrwi();
    void srrsi();
    void srrci();
};


class CSR : public System {
public:
    CSR(uint32_t const is, uint64_t const pc)
        : System(is,pc), m_index_csr(m_func12)
    {
        if (static_cast<uint8_t>(m_func3) < 5) { 
            // TODO: solve the problem, possible reason: alias works internally, not externally. Easiest solution: delete alias and write System::func3_t
            m_csr_aux = new CSRImm(m_func3);
        } else {
            m_csr_aux = new CSRNotImm(m_func3);
        }
    }
    void readRegister(reg_type const&) override;
    void readCSR(const csrs_t &) override;
    void execution() override;
    void writeCsr(csrs_t& csrs) override;
    void writeBack(reg_type &) override;
private:
    CSRAux* m_csr_aux;
    uint16_t const& m_index_csr;
    uint64_t m_rs1;
    uint64_t m_csr_rs; // alias t in riscv instructions
    uint64_t m_csr_rd;
    uint64_t m_rd;
}; 
