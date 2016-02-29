cmake_minimum_required(VERSION 3.0)

project(Elchcraft)

add_definitions(-std=c++11)

set(GLFW_BUILD_EXAMPLES off)
set(GLFW_BUILD_TESTS off)
set(GLFW_BUILD_DOCS off)
set(GLFW_INSTALL off)
add_subdirectory(3rd-party/glfw)

find_package(GLEW REQUIRED)

set(CPACK_PACKAGE_NAME "Elchcraft")
set(CPACK_PACKAGE_VENDOR "LittleFox")
set(CPACK_PACKAGE_CONTACT "Moritz \\\"LittleFox\\\" Grosch <littlefox@lf-net.org>")
set(CPACK_PACKAGE_VERSION "0.0.1-nightly")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Elchcraft")
set(CPACK_PACKAGE_EXECUTABLES "elchcraft;Elchcraft")
include(CPack)

include_directories(
    ${GLEW_INCLUDE_DIRS}
    3rd-party/glfw/include
	3rd-party/glm
)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
add_definitions(-DINSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")

add_library(eccommon STATIC
    common/src/loadhandler.cpp
)

add_library(ecgraphics STATIC
    graphics/src/rendertargetwindow.cpp
    graphics/src/scene.cpp
    graphics/src/objectwavefront.cpp
)

add_executable(elchcraft
    elchcraft/src/main.cpp
)

if(WIN32)
    set(SYSTEM_SPECIFIC_LIBRARIES opengl32)

    if(GLEW_DLL)
        install(FILES "${GLEW_DLL}" DESTINATION bin)
    endif()
else()
    set(SYSTEM_SPECIFIC_LIBRARIES GL)
endif()

target_link_libraries(ecgraphics eccommon glfw ${GLEW_LIBRARIES} ${SYSTEM_SPECIFIC_LIBRARIES})
target_link_libraries(elchcraft ecgraphics eccommon glfw ${GLEW_LIBRARIES} ${SYSTEM_SPECIFIC_LIBRARIES})

install(TARGETS elchcraft ecgraphics eccommon
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
install(DIRECTORY elchcraft/res DESTINATION share/Elchcraft)
