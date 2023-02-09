project(emulator)

file(GLOB emulator_sources CONFIGURE_DEPENDS *.hpp *.cpp components/*.hpp components/*.cpp)

# check
#add_subdirectory(components)

add_library(
    emulator
    ${emulator_sources}
)
