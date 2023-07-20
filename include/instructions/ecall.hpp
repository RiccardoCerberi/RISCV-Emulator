#pragma once

#include"system.hpp"
#include <cstdint>

// Ecall differs from Ebreak for the func12 bits
class Ecall : public System {
    public:
        Ecall(InstructionSize_t const is, Address_t const pc)
            : System(is, pc)
        {}
        // implementation beyond ui instructions
        void execution() override {
            std::cout << "Calling to operative system\n";
        } 
};
