#pragma once

#include "instructions.hpp"

/*
 * I-format:
 * - rd => register that will store the result
 * - func3 => specifies the instruction variant (addi, jalr)
 * - rs1 => source register
 * - immediate
 */

class I : public InstructionFormat{
    public:
        void readRegister(Registers const&) override;
        void writeBack(Registers&) override;
    protected:
        // There are duplicated func3, so I decided to append two digits in order to distinguish all operations
        enum class id_t : uint8_t {
            kaddi = 0b00000,
            kslli = 0b00001,
            kslti = 0b00010, // boolean, true is rs1 < imm (signextended) considering both as signed numbers
            ksltiu = 0b00011, // boolean, true is rs1 < imm (unsigned) considering both as unsigned integer
            kxori = 0b00100,
            ksrli = 0b00101,
            ksrai = 0b01101,
            kori = 0b00110,
            kandi = 0b00111,
        };

        I(uint32_t const is, uint64_t const pc) 
            : InstructionFormat(is, pc), 
            m_index_rs(takeRegS()), 
            m_index_rd(takeRegD()), 
            m_offset(takeOffset()),
            m_id(takeId())
    {}
    private:
        size_t takeRegS();
        size_t takeRegD();
        uint64_t takeOffset();
        id_t takeId();
    protected:
        size_t m_index_rs;
        size_t m_index_rd;
        uint64_t m_offset;
        id_t m_id;

        uint64_t m_rs;
        uint64_t m_rd;
};
