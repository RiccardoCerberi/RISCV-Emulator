#setup the cmake version
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(riscv-emulator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

set(deb_flags "-DDEBUG=1")
set(gcc_flags "-Wall;-Wextra;-Wshadow;-Wshadow;-Wformat=2;$<$<CONFIG:Debug>:${deb_flags}>")
set(msvc_flags "-W3")

add_subdirectory(src)

add_executable(riscv-emulator main.cpp)

target_link_libraries(
    riscv-emulator emulator
)

set_target_properties(riscv-emulator
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>")

target_compile_features(riscv-emulator PUBLIC cxx_std_20)

target_compile_options(riscv-emulator PRIVATE
   "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${gcc_flags}>>"
   "$<${msvc_cxx}: $<BUILD_INTERFACE:${msvc_flags}>>")


