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

target_link_libraries(emulator PUBLIC emulator_headers)

# compilation flags
target_compile_features(emulator PUBLIC cxx_std_20)

target_compile_options(emulator PRIVATE
   "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${gcc_flags}>>"
   "$<${msvc_cxx}: $<BUILD_INTERFACE:${msvc_flags}>>")
