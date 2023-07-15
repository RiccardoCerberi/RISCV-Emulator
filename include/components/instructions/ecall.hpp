#pragma once

#include"system.hpp"
#include <cstdint>

// Ecall differs from Ebreak for the func12 bits
class Ecall : public System {
    public:
        Ecall(uint32_t const is, uint64_t const pc)
            : System(is, pc)
        {}
        // TODO: implement this function
        void execution() override{
            throw "Ecall not implemented yet\n";
        } 
};
