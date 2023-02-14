#include"system.hpp"
#include <cstdint>

class Ecall : public System {
    public:
        Ecall(uint32_t const is, uint64_t const pc)
            : System(is, pc)
        {}
        // TODO: implement the execute function
};
