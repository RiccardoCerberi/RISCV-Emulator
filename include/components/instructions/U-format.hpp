#include"instructions.hpp"
#include <cstdint>

class U : public InstructionFormat {
    public:
        U(uint32_t const is, uint64_t const pc) 
        : InstructionFormat(is,pc),
          m_offset(takeOffset()),
          m_index_rd(takeRd())
    {}
        void writeBack(reg_type&) override;
    private:

        uint32_t takeOffset();
        size_t takeRd();

        uint32_t m_offset;
        size_t m_index_rd;
};

