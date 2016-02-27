#ifndef _GRAPHICS_OBJECTTRIANGLE_H_INCLUDED
#define _GRAPHICS_OBJECTTRIANGLE_H_INCLUDED

#include "objectarray.h"

namespace Elchcraft {
    namespace Graphics {
        class ObjectTriangle : public ObjectArray {
            public:
                ObjectTriangle() {
                    static const GLfloat data[] = {
                        -1.0f, -1.0f,  0.1f,
                         1.0f, -1.0f,  0.1f,
                         1.0f, -1.0f, -0.1f,

                        -1.0f, -1.0f,  0.1f,
                         1.0f, -1.0f, -0.1f,
                        -1.0f, -1.0f, -0.1f,

                        -1.0f, -1.0f, -0.1f,
                         1.0f, -1.0f, -0.1f, 
                         0.0f,  1.0f, -0.1f,

                        -1.0f, -1.0f,  0.1f,
                         1.0f, -1.0f,  0.1f,
                         0.0f,  1.0f,  0.1f,
                    };

                    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
                }

                void render() {
                    ObjectArray::render();
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                    glDrawArrays(GL_TRIANGLES, 0, 12);
                }
        };
    }
}

#endif
