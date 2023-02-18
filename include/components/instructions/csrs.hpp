#pragma once

#include"system.hpp"
#include"../bits-manipulation.hpp"
#include <cstdint>

/*
 * Every instruction of this type consists in 
 * - Reading value from csrs
 * - doing some operations, producing the result
 * - swapping the result with register rd
 */

/*
 * CSRAUx defines the interface for immediate and non operations with CSRs
 */

class CSRAux {
protected:
    using func3_t = System::func3_t;
public:
    CSRAux(System::func3_t const func3, uint8_t const qty) 
        : m_func3(func3), m_qty(qty)
    {}
// If the CSRs instructions is a non immediate operations, then it will read
// data from the normal registers (the ones from 0 to 31) based on the qty, in fact it becomes an index in the registers vector;
// otherwise the quantity refers to an immediate, so it will use it just for making
// the result 
    virtual void InterpretQty(reg_type const&) {}
    virtual uint64_t makeCSRResult(uint64_t const) = 0;
protected:
    func3_t m_func3;
    uint8_t m_qty; //it can be either an immediate for csri instructions or an id to distinguish non-immediate instructions
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
    // distinguish between the two possible cases: immediate or operations id
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
            m_csr_aux = new CSRImm(m_func3, BitsManipulation::takeBits(is,15,19));
        } else {
            m_csr_aux = new CSRNotImm(m_func3, BitsManipulation::takeBits(is,15,19));
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
