#include"../../include/components/instructions.hpp"
#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <sys/types.h>

// Default functions

void InstructionFormat::readRegister(const reg_type &) {}

void InstructionFormat::accessMemory(Bus&) {}

void InstructionFormat::writeBack(reg_type&) {}

uint64_t InstructionFormat::moveNextInstruction() { 
    return m_curr_pc + data_size::kword; 
}

// Jump
void Jis::execution() {
    m_reg_save_pcis = BitsManipulation::takeBits(m_instruction, 7, 11);
    // the immediate recevied it's in half word, to report
    // it in byte it's needed a left shifting of 1
    m_immediate =
        BitsManipulation::extendSign(BitsManipulation::takeBits(m_instruction, 21, 30) << 1 | BitsManipulation::takeBits(m_instruction, 20, 20) << 11 |
                   BitsManipulation::takeBits(m_instruction, 12, 19) << 12 | BitsManipulation::takeBits(m_instruction, 31, 31) << 20);
#ifdef DEBUG
    std::binset<data_size::kword> is_bin(is);
    std::cout << "Instruction: " << is_bin << "\nImmediate=" << imm << "\n";
#endif
}

void Jis::writeBack(reg_type& registers) {
    registers[m_reg_save_pcis] =  + data_size::kword;
}

uint64_t Jis::moveNextInstruction() {
    return m_curr_pc + m_immediate;
}


// I-format


size_t I::takeRegS() {
    return BitsManipulation::takeBits(m_instruction,15,19);
}

size_t I::takeRegD(){
    return BitsManipulation::takeBits(m_instruction, 7, 11);
}

uint64_t I::takeImm() {
    return BitsManipulation::extendSign(BitsManipulation::takeBits(m_instruction, 20, 31));
}


// TODO: testing
I::func3_t I::takeFunc3() {
    return I::func3_t(BitsManipulation::takeBits(m_instruction, 12, 14));
}

void I::readRegister(const reg_type & regs) {
    m_rs = regs[m_index_rs];
}

void I::writeBack(reg_type &regs) {
    regs[m_index_rd] = m_rd;
}

// Jris
void Jris::execution() {
    m_rd = m_curr_pc + data_size::kword;
}

uint64_t Jris::moveNextInstruction() {
    return (m_rs + m_immediate) 
            & (static_cast<uint64_t>(-1) >>  (sizeof(uint64_t)*8 - 1));
}
/*
 *  
    enum class func3 : uint8_t {
        kaddi = 0b000,
        kslti = 0b010,
        ksltiu = 0b011,
        kxori = 0b100,
        kori = 0b110,
        kandi = 0b111,
        kslli = 0b001,
        ksrli = 0b101,
        ksrai = 0b101
    };
 */

void ImmOp::addi() {
    m_rd = m_rs + m_immediate;
}

void ImmOp::slti() {
    if (static_cast<int64_t>(m_rs) < static_cast<int64_t>(m_immediate)) {
        m_rd = 1;
    } else  {
        m_rd = 0;
    }
}

void ImmOp::sltiu() {
    if (m_rs < m_immediate) {
        m_rd = 1;
    } else {
        m_rd = 0;
    }
}

void ImmOp::xori() {
    m_rd = m_rs ^ m_immediate;
}


void ImmOp::ori() {
    m_rd = m_rs | m_immediate;
}

void ImmOp::andi() {
    m_rd = m_rs & m_immediate;
}

void ImmOp::slli() {
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = m_rs << shamt;
}

void ImmOp::srli() {
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    m_rd = m_rs >> shamt;
}

void ImmOp::srai() {
    uint64_t shamt = BitsManipulation::takeBits(m_instruction, 20, 24);
    uint64_t vacant_bit = static_cast<uint64_t>(1) << (sizeof(uint64_t)*8 -1);
    m_rd = (vacant_bit & m_rs) | (m_rs >> shamt);
}



void ImmOp::execution() {
    // see enum class in switch
    switch(m_func3) {
        case func3_t::kaddi:
            addi();
            break;
        // finish other cases
            
    }
}










