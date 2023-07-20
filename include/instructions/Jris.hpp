#pragma once
#include "I-format.hpp"

class Jris : public I {
    public:
        Jris(InstructionSize_t const is, Address_t const pc) : I(is,pc) {}
        void execution() override;
        Address_t moveNextInstruction() override;
        ~Jris() = default;
    private:
        RegisterSize_t m_reg;
};
