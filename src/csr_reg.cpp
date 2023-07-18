#include"../include/csr_reg.hpp"

void CSRInterface::write(Address_t write_to, uint64_t what) {
    assert(checkLimit(write_to));
    assert(getPermission(write_to) != 3);
    m_csrs[write_to]  = what;
}

uint64_t CSRInterface::read(Address_t where) const {
    assert(checkLimit(where));
    return m_csrs[where];
}


void CSRInterface::updateTimer() {
    m_csrs[time_address]  += 1;
}

