#include "I-format.hpp"

class Jris : public I {
    public:
        Jris(uint32_t const is, uint64_t const pc) : I(is,pc) {}
        void execution() override;
        uint64_t moveNextInstruction() override;
        ~Jris() = default;
    private:
        uint64_t m_reg;
};
