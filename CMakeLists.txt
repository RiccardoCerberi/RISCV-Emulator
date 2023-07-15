#setup the cmake version
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

#Note: R in upper case
project(riscv-emulator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

#headers always before sources
add_subdirectory(include)
add_subdirectory(src)

add_executable(riscv-emulator main.cpp)

target_link_libraries(
        riscv-emulator
        PRIVATE
        components
        emulator
)

set_target_properties(riscv-emulator
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>")

target_compile_features(riscv-emulator PUBLIC cxx_std_17)

set(gcc_flags "-Wall;-Wextra;-Wshadow;-Wshadow;-Wformat=2;-g;-DDEBUG")
set(msvc_flags "-W3")

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(riscv-emulator PRIVATE
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${gcc_flags}>>"
   "$<${msvc_cxx}: $<BUILD_INTERFACE:${msvc_flags}>>")

if (DEBUG)
    message("DEBUG flag")
    add_definitions(-DDEBUG=1)
else()
    message("No DEBUG flag")
endif (DEBUG)

