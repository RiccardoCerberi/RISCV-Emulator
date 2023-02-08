project(emulator)

file(GLOB emulator_sources *.hpp *.cpp)

add_library(
    emulator
    emulator_sources
)
