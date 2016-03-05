#ifndef _GRAPHICS_OBJECT_H_INCLUDED
#define _GRAPHICS_OBJECT_H_INCLUDED

#include <GL/glew.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace Elchcraft {
    namespace Graphics {
        class Object {
            public:
                Object() 
                    : _translate(glm::mat4(1.0f)),
                      _rotate(glm::mat4(1.0f)), 
                      _scale(glm::mat4(1.0f)) {
                }

                virtual ~Object() {
                }

                virtual void render() {
                }

                virtual glm::mat4 getMatrix() {
                    return _translate * _rotate * _scale;
                }

                virtual void translate(float x, float y, float z) {
                    _translate = glm::translate(_translate, glm::vec3(x, y, z));
                }

                virtual void rotate(float angle, float x, float y, float z) {
                    _rotate = glm::rotate(_rotate, angle, glm::vec3(x, y, z));
                }

                virtual void scale(float x, float y, float z) {
                    _scale = glm::scale(_scale, glm::vec3(x, y, z));
                }

            protected:
                glm::mat4 _translate;
                glm::mat4 _rotate;
                glm::mat4 _scale;
        };
    }
}

#endif
