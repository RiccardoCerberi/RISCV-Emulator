#pragma once

#include"U-format.hpp"


class Lui : public U {
public:
    Lui(uint32_t const is, uint64_t const pc)
     : U(is, pc)
    {}
    void execution() override;
};