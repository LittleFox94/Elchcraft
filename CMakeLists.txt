cmake_minimum_required(VERSION 3.0)

project(Elchcraft)

option(GLFW_BUILD_EXAMPLES off)
option(GLFW_BUILD_TESTS off)
option(GLFW_BUILD_DOCS off)
option(GLFW_INSTALL off)
add_subdirectory(3rd-party/glfw)

find_package(GLEW REQUIRED)

set(CPACK_PACKAGE_NAME "Elchcraft")
set(CPACK_PACKAGE_VENDOR "LittleFox")
set(CPACK_PACKAGE_CONTACT "Moritz \\\"LittleFox\\\" Grosch <littlefox@lf-net.org>")
set(CPACK_PACKAGE_VERSION "0.0.1-nightly")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Elchcraft")
set(CPACK_PACKAGE_EXECUTABLES "elchcraft;Elchcraft")
set(CPACK_BUNDLE_NAME "Elchcraft")
set(CPACK_BUNDLE_PLIST "${CMAKE_SOURCE_DIR}/dist/osx/Info.plist")
#set(CPACK_BUNDLE_STARTUP_COMMAND "bin/elchcraft")
set(CPACK_BUNDLE_ICON "${CMAKE_SOURCE_DIR}/dist/osx/Info.plist")
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
target_compile_features(eccommon PRIVATE cxx_nullptr cxx_auto_type cxx_range_for)

add_library(ecgraphics STATIC
    graphics/src/rendertargetwindow.cpp
    graphics/src/scene.cpp
    graphics/src/objectwavefront.cpp
)
target_compile_features(ecgraphics PRIVATE cxx_nullptr cxx_auto_type cxx_range_for)

add_executable(elchcraft
    elchcraft/src/main.cpp
)
target_compile_features(elchcraft PRIVATE cxx_nullptr cxx_auto_type cxx_range_for)

if(WIN32)
    set(SYSTEM_SPECIFIC_LIBRARIES opengl32)

    if(GLEW_DLL)
        install(FILES "${GLEW_DLL}" DESTINATION bin)
    endif()
elseif(APPLE)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    set(SYSTEM_SPECIFIC_LIBRARIES ${OPENGL_LIBRARIES})
else()
    set(SYSTEM_SPECIFIC_LIBRARIES GL)
endif()

target_link_libraries(ecgraphics eccommon glfw ${GLEW_LIBRARIES} ${SYSTEM_SPECIFIC_LIBRARIES})
target_link_libraries(elchcraft ecgraphics eccommon glfw ${GLEW_LIBRARIES} ${SYSTEM_SPECIFIC_LIBRARIES})

install(TARGETS elchcraft
    RUNTIME DESTINATION bin
)
install(DIRECTORY elchcraft/res DESTINATION share/Elchcraft)
