cmake_minimum_required(VERSION 3.0)

project(Elchcraft)

add_definitions(-std=c++11) 
add_subdirectory(3rd-party/glfw)

find_package(GLEW REQUIRED)

include_directories(
    ${GLEW_INCLUDE_DIRS}
    3rd-party/glfw/include
	3rd-party/glm
)

add_library(ecgraphics
    graphics/src/rendertargetwindow.cpp
    graphics/src/scene.cpp
    graphics/src/objectwavefront.cpp
)

add_executable(elchcraft
    elchcraft/src/main.cpp
)

target_link_libraries(ecgraphics glfw ${GLEW_LIBRARIES} opengl32)
target_link_libraries(elchcraft ecgraphics)
