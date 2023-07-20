#pragma once 

#include"R-format.hpp"

class Op : public R {
    public:
        Op(InstructionSize_t const is, Address_t const pc)
            : R(is,pc)
        {}
        void execution() override;
    private:
        void add();
        void sub();
        void sll();
        void slt();
        void sltu();
        void xorop();
        void srl();
        void sra();
        void orop();
        void andop();
        void printInstruction(std::string const& is_name, std::string const& op);
};
    
