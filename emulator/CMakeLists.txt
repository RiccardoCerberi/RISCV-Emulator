project(emulator)

file(GLOB emulator_sources *.hpp *.cpp)

# check
add_subdirectory(components)

add_library(
    emulator
    ${emulator_sources}
    components
)
