#pragma once

#include"U-format.hpp"

class Auipc : public U {
public:
    Auipc(InstructionSize_t const is, Address_t const pc)
        : U(is, pc)
    {}
    void execution() override;
};
