#pragma once

#include"constants.hpp"
#include<cassert>

// CSRs registers: CSRs mode ([8,9]) and protection ([10,11])
class CSRInterface{
    public:
        CSRInterface() : m_csrs{0} {}
        void write(Address_t, uint64_t);
        uint64_t read(Address_t) const;
    private:
        static constexpr uint8_t kmode_beg = 8;
        static constexpr uint8_t kperm_beg = 10;
    private:
        uint8_t getMode(Address_t a) const { return a >> kmode_beg; }
        uint8_t getPermission(Address_t a) const{ return  a >> kperm_beg; }
        bool checkLimit(Address_t a) const { return 0 <= a && a < kcsrs_size; }
    private:
        std::array<uint64_t, kcsrs_size> m_csrs;
};
