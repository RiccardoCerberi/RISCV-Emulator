project(interface)

file(GLOB interface_sources *.hpp *.cpp)

add_library(
    interface
    interface_sources
)
