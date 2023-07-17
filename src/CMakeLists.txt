project(${CMAKE_PROJECT_NAME} )

#TODO: change target to avoid recompilation of all sources even if when they're untouched
set(SRCS 
bits-manipulation.cpp 
cpu.cpp
emulator.cpp
memory.cpp
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

#testing building library
add_library(
    components
    STATIC
    ${SRCS}
)



