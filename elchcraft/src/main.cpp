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

    Elchcraft::Graphics::Shader shader("#version 330 core\n"
                                       "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
                                       "uniform mat4 modelMatrix;\n"
                                       "uniform mat4 projectionViewMatrix;\n"
                                       "void main() {\n"
                                       "    gl_Position = projectionViewMatrix * modelMatrix * vec4(vertexPosition_modelspace, 1);\n"
                                       "}", 
                                       "#version 330 core\n"
                                       "out vec3 color;\n"
                                       "void main() {\n"
                                       "    color = vec3(1, gl_FragCoord.x / 1280, 0);\n"
                                       "}");
    window.setShader(&shader);

    Elchcraft::Graphics::ObjectWavefront elk("Elk_f/Elk_f.obj");
    elk.scale(0.6, 0.6, 0.6);
    scene.addObject(&elk, 0);

    Elchcraft::Graphics::ObjectWavefront mini("mini_obj.obj");
    mini.scale(0.002, 0.002, 0.002);
    mini.translate(400, 0, 0);
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
