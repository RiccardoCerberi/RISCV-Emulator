#pragma once

#include"U-format.hpp"


class Lui : public U {
public:
    Lui(InstructionSize_t const is, Address_t const pc)
     : U(is, pc)
    {}
    void execution() override;
};