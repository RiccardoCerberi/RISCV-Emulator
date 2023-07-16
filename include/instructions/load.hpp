#pragma once

#include "I-format.hpp"

// func3 is the width of the data; for example: lw width = 4, ld width = 8 and so on.
class Load : public I {
    public:
        Load(uint32_t const is, uint64_t const pc) : I(is, pc) {}
        void execution() override;
        void accessMemory(SystemInterface&) override;
};
