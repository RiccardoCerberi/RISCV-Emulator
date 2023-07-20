#pragma once

#include "I-format.hpp"


// addi, etc
class ImmOp : public I {
    private:
        // There are two duplicated func3 for which we need additional
        // info: the two last bits of the immediate.
        enum class func3_t : uint8_t {
            kaddi  = 0b000,
            kslli  = 0b001,
            kslti  = 0b010,
            ksltiu = 0b011,
            kxori  = 0b100,
            ksrli  = 0b101,
            ksrai  = 0b101,
            kori   = 0b110,
            kandi  = 0b111,
        };
    public:
        ImmOp(InstructionSize_t const is, Address_t const pc) : I(is,pc), m_func3{I::m_func3} {}
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
        func3_t m_func3;
};
