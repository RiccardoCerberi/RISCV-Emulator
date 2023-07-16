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

class CSRAux;

class CSR : public System {
public:
    CSR(uint32_t const is, uint64_t const pc);
    void readRegister(reg_type const&) override;
    void readCSR(const csrs_t &) override;
// execution function makes the result for modify the csr
// register at index m_index_csr
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
    uint8_t m_qty; //it can be either an immediate for csri operations or an id to distinguish non-immediate operations
};

class CSRNotImm : public CSRAux {
public: 
    CSRNotImm(func3_t const func3, uint8_t const qty) 
        : CSRAux(func3, qty)
    {}
    // in this case, qty represents the index of the register
    // rs1, which is the operand in the functions srrw etc
    void InterpretQty(reg_type const&) override;
    // based on the qty it executes one function between
    // srrw, srrr, srrc
    uint64_t makeCSRResult(uint64_t const) override;
private:
    uint64_t csrrw(uint64_t const);
    uint64_t csrrs(uint64_t const);
    uint64_t csrrc(uint64_t const);

// it stores the content of the register at qty index.
    uint64_t m_rs1; 
};

class CSRImm : public CSRAux {
public: 
    CSRImm(func3_t const func3, uint8_t const qty) 
        : CSRAux(func3,qty)
    {}
    // it zero-extends the immediate 
    void InterpretQty(reg_type const&) override; 
    uint64_t makeCSRResult(uint64_t const) override;
private:
    uint64_t csrrwi(uint64_t const);
    uint64_t csrrsi(uint64_t const);
    uint64_t csrrci(uint64_t const);

    uint64_t m_imm;
};

