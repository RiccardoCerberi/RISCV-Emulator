#pragma once 

#include"R-format.hpp"

class Op : public R {
    public:
        Op(uint32_t const is, uint64_t const pc)
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
};
    
