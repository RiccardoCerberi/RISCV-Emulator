#include "instructions.hpp"

//  I-format 
//  Every I-instruction reads register and saves the result. 
//  What distinguishes every instruction is the execute function that
//  setup the source register or the destination one, that will be written back.
//  operation, like saving the next instruction (jalr)
class I : public InstructionFormat{
    public:
        void readRegister(reg_type const&) override;
        void writeBack(reg_type&) override;
    protected:
        // There are duplicated func3, so the identifier appends the two last immediate 
        // bits to distinguish every instructions
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
        uint64_t m_offset;
        size_t m_index_rs;
        size_t m_index_rd;
        id_t m_id;

        uint64_t m_rs;
        uint64_t m_rd;
};
