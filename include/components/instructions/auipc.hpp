#include"U-format.hpp"

class Auipc : public U {
public:
    Auipc(uint32_t const is, uint64_t const pc)
        : U(is, pc)
    {}
    void execution() override;
};