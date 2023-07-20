#pragma once

#include "I-format.hpp"

// func3 indicates the width of the data.
class Load : public I {
    public:
        Load(InstructionSize_t const is, Address_t const pc) : I(is, pc) {}
        void execution() override;
        void accessMemory(SystemInterface&) override;
    private:
        Address_t m_ad_to_read;
};
