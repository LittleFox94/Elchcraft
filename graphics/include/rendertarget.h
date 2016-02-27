#ifndef _GRAPHICS_RENDERTARGET_H_INCLUDED
#define _GRAPHICS_RENDERTARGET_H_INCLUDED

#include "scene.h"
#include "shader.h"

namespace Elchcraft {
    namespace Graphics {
        class RenderTarget {
            public:
                RenderTarget()
                    : _viewMatrix(glm::mat4(1.0f)),
                      _projectionMatrix(glm::mat4(1.0f)),
                      _projectionViewMatrix(glm::mat4(1.0f)) {
                }

                virtual void makeCurrent() = 0;
                virtual void drawScene(Scene const& scene) = 0;

                virtual void setProjectionMatrix(glm::mat4 matrix) {
                    _projectionMatrix = matrix;
                    _projectionViewMatrix = _projectionMatrix * _viewMatrix;

                    if(_currentShader != nullptr) {
                        _currentShader->setProjectionViewMatrix(_projectionViewMatrix);
                    }
                }

                virtual void setViewMatrix(glm::mat4 matrix) {
                    _viewMatrix = matrix;
                    _projectionViewMatrix = _projectionMatrix * _viewMatrix;

                    if(_currentShader != nullptr) {
                        _currentShader->setProjectionViewMatrix(_projectionViewMatrix);
                    }
                }

                virtual void setShader(Shader* shader) {
                    _currentShader = shader;
                    _currentShader->setProjectionViewMatrix(_projectionViewMatrix);
                }

            protected:
                Shader* _currentShader;
                glm::mat4 _projectionMatrix;
                glm::mat4 _viewMatrix;
                glm::mat4 _projectionViewMatrix;
        };
    }
}

#endif
