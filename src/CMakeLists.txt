project(${CMAKE_PROJECT_NAME} )

set(SRCS 
bits-manipulation.cpp 
cpu.cpp
emulator.cpp
memory.cpp
)

#testing building library
add_library(
    components
    STATIC
    ${SRCS}
)



