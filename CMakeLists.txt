#setup the cmake version
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)


project( riscV-emulator )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directory( include ) # for header files
add_subdirectory( src ) # for the implementation files of the headers

set_target_properties(riscV-emulator
    PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>")

target_compile_features(riscV-emulator PUBLIC cxx_std_17)

# add compiler warning flags just when building this project
# via the BUILD_INTERFACE generator expression
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

set(gcc_flags "-Wall;-Wextra;-Wshadow;-Wshadow;-Wformat=2;-g")
set(msvc_flags "-W3")

target_compile_options(riscV-emulator PRIVATE
     "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${gcc_flags}>>"
        "$<${msvc_cxx}: $<BUILD_INTERFACE:${msvc_flags}>>")
