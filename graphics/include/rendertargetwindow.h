#ifndef _GRAPHICS_RENDERTARGETWINDOW_H_INCLUDED
#define _GRAPHICS_RENDERTARGETWINDOW_H_INCLUDED

#include "rendertarget.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Elchcraft {
    namespace Graphics {
        class RenderTargetWindow : public RenderTarget {
            public:
                RenderTargetWindow();
                virtual ~RenderTargetWindow();

                bool active();
                void makeCurrent();
                void eventProcessor();

                void drawScene(Scene const& scene);

            private:
                bool _active;
                GLFWwindow* _window;
        };
    }
}

#endif
