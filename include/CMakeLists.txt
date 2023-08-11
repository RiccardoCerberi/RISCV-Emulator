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

# To show up headers in IDE we need to make a target.
add_library(
    emulator_headers
    INTERFACE
    ${components_headers}
    ${instructions_headers}
)

list(APPEND include_path "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/instructions")

target_include_directories(emulator_headers 
    INTERFACE 
    "$<BUILD_INTERFACE:${include_path}>"
    "$<INSTALL_INTERFACE:${include_path}>"
)


