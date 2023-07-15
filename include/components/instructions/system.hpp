#pragma once

#include"instructions.hpp"
#include <cstdint>
#include <memory>

/*
 * Fence and CSRs are instructions that divided the string of bits in the same way, the only difference is the interpretation they give to the chuncks generated
 */

class System : public InstructionFormat {
public:
    System(uint32_t const is, uint64_t const pc)
        : InstructionFormat(is,pc), 
          m_index_rd(takeRd()),
          m_qty(takeQty()),
          m_func3(takeFunc3()),
          m_func12(takeFunc12())
    {}
    enum class func3_t : uint8_t {
        kecall = 0b000,
        kebreak = 0b000,
        kcsrrw = 0b001,
        kcsrrs = 0b010,
        ksrrc = 0b011,
        kcsrrwi = 0b101,
        ksrrsi = 0b110,
        kcsrrci = 0b111
    };

    private:
        size_t takeRd();
        uint8_t takeQty();
        func3_t takeFunc3();
        uint16_t takeFunc12();
    protected:
        size_t m_index_rd;
        uint8_t m_qty; // to distinguish from immediate and normal csrs opearation
        func3_t m_func3;
        uint16_t m_func12;
};


