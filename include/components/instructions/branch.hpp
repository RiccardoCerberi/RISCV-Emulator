#pragma once
#include <cstddef>
#include <cstdint>
#include "instructions.hpp"

class Branch : public InstructionFormat {
    public:
        Branch(uint32_t const is, uint64_t const pc) 
            : InstructionFormat(is,pc),
            m_index_rs1(takeRs1()),
            m_index_rs2(takeRs2()),
            m_offset(takeOffset()),
            m_id_cond(takeIdCond()),
            m_jump(false)
    {}    
        void readRegister(reg_type const&) override;

         void execution() override;
         uint64_t moveNextInstruction()override;

    private:
        enum class id_t {
            kbeq = 0b000,
            kbne = 0b001,
            kblt = 0b100,
            kbge = 0b101,
            kbltu = 0b110,
            kbgeu = 0b111
        };

        size_t takeRs1();
        size_t takeRs2();
        uint16_t takeOffset();
        id_t takeIdCond();

        size_t m_index_rs1;
        size_t m_index_rs2;
        uint64_t m_offset;
        // distinguish every conditions
        id_t m_id_cond;

        uint64_t m_rs1;
        uint64_t m_rs2;
        bool m_jump;

        bool beq();
        bool bne();
        bool blt();
        bool bge();
        bool bltu();
        bool bgeu();
};
