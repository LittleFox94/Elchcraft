#ifndef _GRAPHICS_OBJECTARRAY_H_INCLUDED
#define _GRAPHICS_OBJECTARRAY_H_INCLUDED

#include "object.h"

#include <GL/glew.h>
#include <GL/gl.h>

namespace Elchcraft {
    namespace Graphics {
        class ObjectArray : public Object {
            public:
                ObjectArray() {
                    glGenVertexArrays(1, &_vertexArrayID);
                    glBindVertexArray(_vertexArrayID);

                    glGenBuffers(1, &_vertexBuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
                }

                virtual ~ObjectArray() {
                    glDeleteBuffers(1, &_vertexBuffer);
                    glDeleteVertexArrays(1, &_vertexArrayID);
                }

                virtual void render() {
                    glBindVertexArray(_vertexArrayID);
                }

            protected:
                GLuint _vertexArrayID;
                GLuint _vertexBuffer;
        };
    }
}

#endif
