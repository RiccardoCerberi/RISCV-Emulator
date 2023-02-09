#pragma once

#include <vector>
#include <cstdint>
#include<iostream>
#include "constants.hpp"

/*
 * TODO: configure ecall to implement system calls.
    L21 of the MIT from 6:57 there's the implemenetation
*/



    // Registers cannot be pointers because they have to support all the operations like addiction or subtraction
    // as well as deferencing; this will require casting, maybe I could define a function just
    // for custing, maybe it would require some changes.

    // NOTE: difference like t1 - t0 where the address of t1 < t0 will have strange effect
    // also because they're unsigned so the subtraction will always result in a positive integers.

    // NOTE: operations between registers differ one from another by the type involved for example integers
    // or chars; see the test/test.cpp file.

    // TODO: set "special" registers like register0

class CPU {
public:
    CPU();
private:
    std::vector<uint64_t> m_registers;
    uint64_t m_pc; // it's the 32-th register

    // steps
    //void fetch();
    //void decode();
    //void execute();
    //void writeBack();
};