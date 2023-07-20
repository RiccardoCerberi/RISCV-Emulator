#pragma once 
#include"instructions.hpp"


class Fence : public InstructionFormat {
    public:
        Fence(uint32_t const is, uint64_t const pc)
            : InstructionFormat(is,pc) {}
    void execution() override {
        std::cout << "Fence instruction: synchronization\n";
    }
};