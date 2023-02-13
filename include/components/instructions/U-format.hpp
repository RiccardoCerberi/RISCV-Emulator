#include"instructions.hpp"
#include <cstdint>

class U : public InstructionFormat {
    public:
        U(uint32_t const is, uint64_t const pc) 
        : InstructionFormat(is,pc),
          m_imm(takeImm()),
          m_index_rd(takeRd())
    {}
        void execution() override;
        void writeBack(reg_type&) override;
    private:

        uint32_t takeImm();
        size_t takeRd();

        uint32_t m_imm;
        size_t m_index_rd;
};

