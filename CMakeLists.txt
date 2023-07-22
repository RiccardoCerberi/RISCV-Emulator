#setup the cmake version
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(riscv-emulator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

#boolean variables to know which is the deafult compiler in the system
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

#compiler flags 
set(gcc_flags "-Wall;-Wextra;-Wunused;-Wshadow;-Wformat=2;-g;-O2;-DDEBUG=1;")
set(msvc_flags "-W3")

add_compile_options(
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${gcc_flags}>>"
   "$<${msvc_cxx}: $<BUILD_INTERFACE:${msvc_flags}>>")

#headers always before sources
add_subdirectory(include)
add_subdirectory(src)

add_executable(riscv-emulator main.cpp)

target_link_libraries(
        riscv-emulator
        PRIVATE
        emulator
)

set_target_properties(riscv-emulator
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>")

if (DEBUG)
    message("DEBUG flag is set")
    add_definitions(-DDEBUG=1)
else()
    message("No DEBUG flag")
endif (DEBUG)

