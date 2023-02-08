project(components)

file(GLOB components_sources *.hpp *.cpp)

add_library(
    components
    ${components_sources}
)
