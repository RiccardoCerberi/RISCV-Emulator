project(${CMAKE_PROJECT_NAME} )

#check if it's syntactically correct <name_folder>/
file(GLOB components_sources CONFIGURE_DEPENDS  components/*.cpp)
file(GLOB emulator_sources emulator/*.cpp)

add_library(
    components 
    ${components_sources}
)
add_library(
    emulator
    ${emulator_sources}
)

#tell cmake where to find headers to solve dependencies
target_include_directories(
    components
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/components
)

target_include_directories(
    emulator
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/emulator
)

target_link_libraries(
    emulator
    PUBLIC
    components
)