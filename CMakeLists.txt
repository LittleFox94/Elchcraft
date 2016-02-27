cmake_minimum_required(VERSION 3.0)

project(Elchcraft)

add_definitions(-std=c++11) 

find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

add_library(ecgraphics
    graphics/src/rendertargetwindow.cpp
    graphics/src/scene.cpp
    graphics/src/objectwavefront.cpp
)

add_executable(elchcraft
    elchcraft/src/main.cpp
)

target_link_libraries(ecgraphics ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} GL)
target_link_libraries(elchcraft ecgraphics)
