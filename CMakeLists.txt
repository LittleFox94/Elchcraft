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

if(WIN32)
    set(SYSTEM_SPECIFIC_LIBRARIES opengl32)
else()
    set(SYSTEM_SPECIFIC_LIBRARIES GL)
endif()

target_link_libraries(ecgraphics glfw ${GLEW_LIBRARIES} ${SYSTEM_SPECIFIC_LIBRARIES})
target_link_libraries(elchcraft ecgraphics glfw ${GLEW_LIBRARIES} ${SYSTEM_SPECIFIC_LIBRARIES})
