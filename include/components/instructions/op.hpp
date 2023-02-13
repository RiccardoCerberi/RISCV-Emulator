#pragma once 

#include"R-format.hpp"

class Op : public R {
    public:
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
    
