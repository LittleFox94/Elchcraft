#include "../include/rendertargetwindow.h"
#include "../../common/include/loadhandler.h"

#include <iostream>
#include <cstdlib>

namespace Elchcraft {
    namespace Graphics {
        RenderTargetWindow::RenderTargetWindow() : _active(true) {
            glfwWindowHint(GLFW_SAMPLES,               16);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE,        GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            _window = glfwCreateWindow(1280, 800, "Elchcraft", NULL, NULL);
            if(_window == nullptr) {
                std::cerr << "Error creating window with glfw3" << std::endl;
                glfwTerminate();
                std::exit(-1);
            }

            makeCurrent();

            glewExperimental = true;
            if(glewInit() != GLEW_OK) {
                std::cerr << "Could not glewInit()!" << std::endl;
                std::exit(-1);
            }

            glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
        }

        RenderTargetWindow::~RenderTargetWindow() {
            // the program exits on window-close
        }

        void RenderTargetWindow::makeCurrent() {
            glfwMakeContextCurrent(_window);
        }

        bool RenderTargetWindow::active() {
            return _active;
        }

        void RenderTargetWindow::eventProcessor() {
            while(Elchcraft::Common::LoadHandler::getInstance()->glFinishLoading());

            glfwSwapBuffers(_window);
            glfwPollEvents();

            _active = glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
                      glfwWindowShouldClose(_window) == 0;
        }

        void RenderTargetWindow::drawScene(Scene const& scene) {
            const std::list<Object*>* objects = scene.getObjects();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            _currentShader->render();

            for(auto object : *objects) {
                _currentShader->setModelMatrix(object->getMatrix());
                object->render();
            }
        }
    }
}
