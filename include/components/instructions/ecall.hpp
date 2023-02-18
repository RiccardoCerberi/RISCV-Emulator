#pragma once

#include"system.hpp"
#include <cstdint>

class Ecall : public System {
    public:
        Ecall(uint32_t const is, uint64_t const pc)
            : System(is, pc)
        {}
        void execution() override{
            std::cerr << "Error, no implementation\n";
            abort();
        } 
        // TODO: implement the execute function
};
