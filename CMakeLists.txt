#setup the cmake version
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(riscv-emulator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(CMAKE_CXX_STANDARD 20)

add_subdirectory(include)
add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
        ${PROJECT_NAME} emulator
)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_features(emulator PUBLIC cxx_std_20)

# add compiler warning flags just when building this project
# via the BUILD_INTERFACE generator expression
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

set(deb_flags "-DDEBUG=1")
set(gcc_flags "-Wall;-Wextra;-Wshadow;-Wshadow;-Wformat=2;$<$<CONFIG:Debug>:${deb_flags}>")
set(msvc_flags "-W3")


target_compile_options(${PROJECT_NAME} PRIVATE
   "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${gcc_flags}>>"
   "$<${msvc_cxx}: $<BUILD_INTERFACE:${msvc_flags}>>")

target_compile_options(emulator PRIVATE
   "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${gcc_flags}>>"
   "$<${msvc_cxx}: $<BUILD_INTERFACE:${msvc_flags}>>")

