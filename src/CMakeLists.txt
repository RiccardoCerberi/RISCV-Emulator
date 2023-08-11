set(instructions 
instructions/auipc.cpp
instructions/branch.cpp
instructions/csrs.cpp
instructions/I-format.cpp
instructions/imm-op.cpp
instructions/instructions.cpp
instructions/Jis.cpp
instructions/Jris.cpp
instructions/load.cpp
instructions/lui.cpp
instructions/op.cpp
instructions/R-format.cpp
instructions/store.cpp
instructions/system.cpp
instructions/U-format.cpp
)

set(components 
bits-manipulation.cpp 
emulator.cpp
cpu.cpp
registers.cpp
csr_reg.cpp
memory.cpp
)

add_library(
    emulator
    STATIC
    ${instructions}
    ${components}
)


list(APPEND include_path "${CMAKE_CURRENT_SOURCE_DIR}/../include" "${CMAKE_CURRENT_SOURCE_DIR}/../include/instructions")

target_include_directories(emulator
  PUBLIC
  "$<BUILD_INTERFACE:${include_path}"
  "$<INSTALL_INTERFACE:${include_path}"
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
