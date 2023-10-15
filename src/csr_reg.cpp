#include "csr_reg.hpp"

void CSRInterface::write(Address_t const write_to, RegisterSize_t const what) {
    assert(checkLimit(write_to));
    if (getPermission(write_to) == 3) {
        throw "try to write read only location";
    }
    m_csrs[write_to] = what;
}

RegisterSize_t CSRInterface::read(Address_t where) const {
    assert(checkLimit(where));
    return m_csrs[where];
}

void CSRInterface::updateTimer() { m_csrs[time_address] += 1; }
