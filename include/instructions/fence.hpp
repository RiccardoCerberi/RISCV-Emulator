#pragma once
#include "instructions.hpp"

class Fence : public InstructionFormat {
public:
    Fence(InstructionSize_t const is, Address_t const pc)
        : InstructionFormat(is, pc) {}
    void execution() override {
        std::cout << "Fence instruction: synchronization\n";
    }
};
