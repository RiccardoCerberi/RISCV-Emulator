project(${CMAKE_PROJECT_NAME} )

#check if it's syntactically correct <name_folder>/
file(GLOB sources CONFIGURE_DEPENDS  components/*.cpp emulator/*.cpp)

add_library(
    riscv-emulator
    ${sources}
)

#tell cmake where to find headers to solve dependencies
target_include_directories(
    riscv-emulator
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
