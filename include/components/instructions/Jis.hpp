#include "instructions.hpp"

class Jis : public InstructionFormat {
    public:
        Jis(uint32_t const is, uint64_t const pc) : InstructionFormat(is,pc){}
        void execution() override;
        void writeBack(reg_type&) override;
        uint64_t moveNextInstruction() override;
        ~Jis() = default;
    private:
        uint64_t m_immediate;
        size_t m_reg_save_pcis;
};
