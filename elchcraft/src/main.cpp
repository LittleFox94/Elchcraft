#include "../../graphics/include/rendertargetwindow.h"
#include "../../graphics/include/objectwavefront.h"
#include "../../graphics/include/shader.h"

#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW3!" << std::endl;
        std::exit(-1);
    }

    Elchcraft::Graphics::RenderTargetWindow window;
    window.makeCurrent();

    window.setViewMatrix(glm::lookAt(
        glm::vec3(4, 3, 3),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    ));

    window.setProjectionMatrix(glm::perspective(glm::radians(45.0f), (float)1280 / (float)800, 0.1f, 100.0f));

    Elchcraft::Graphics::Scene scene;

    Elchcraft::Graphics::Shader shader(INSTALL_PREFIX"/share/Elchcraft/res/shader/main.vert", INSTALL_PREFIX"/share/Elchcraft/res/shader/main.frag");
    window.setShader(&shader);

    Elchcraft::Graphics::ObjectWavefront elk(INSTALL_PREFIX"/share/Elchcraft/res/3ddata/cube.obj");
    elk.scale(0.4, 0.4, 0.4);
    elk.translate(-2, 0, 0);
    scene.addObject(&elk, 0);

    Elchcraft::Graphics::ObjectWavefront mini(INSTALL_PREFIX"/share/Elchcraft/res/3ddata/mini.obj");
    mini.scale(0.009, 0.009, 0.009);
    mini.translate(3, 0, 0);
    scene.addObject(&mini, 0);

    while(window.active()) {
        // input
        //   |- network
        //   |- physics
        //        |- scene-updates
        //             |- render

        window.eventProcessor();
        window.drawScene(scene);

        elk.rotate(0.01, 0.0, 1.0, 0.0);
        mini.rotate(0.01, 0.0, 1.0, 0.0);
    }

    std::exit(0);
}
