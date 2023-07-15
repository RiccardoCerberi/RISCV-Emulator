#pragma once

#include "I-format.hpp"


// addi, etc
class ImmOp : public I {
    public:
        ImmOp(uint32_t const is, uint64_t const pc) : I(is,pc) {}
        void execution() override; 
    private:
        void addi();
        void slti();
        void sltiu();
        void xori();
        void ori();
        void andi();
        void slli();
        void srli();
        void srai();
        void printInstruction(std::string const &is_name, std::string const &op);
};
