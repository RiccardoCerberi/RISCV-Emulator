set(components_headers
bits-manipulation.hpp
constants.hpp
csr_reg.hpp
registers.hpp
cpu.hpp
emulator.hpp
memory.hpp
tlb.hpp
)

set(instructions_headers
instructions/branch.hpp
instructions/I-format.hpp
instructions/Jis.hpp
instructions/store.hpp
instructions/U-format.hpp
instructions/fence.hpp
instructions/instructions.hpp
instructions/R-format.hpp
instructions/system.hpp
)

#add_library(
#    emulator_headers
#    INTERFACE
#    ${components_headers}
#    ${instructions_headers}
#)


