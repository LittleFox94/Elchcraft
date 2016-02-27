#ifndef _GRAPHICS_SHADER_H_INCLUDED
#define _GRAPHICS_SHADER_H_INCLUDED

#include "object.h"

#include <iostream>
#include <string>

namespace Elchcraft {
    namespace Graphics {
        class Shader {
            public:
                Shader(const char* vertex, const char* fragment) {
                    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
                    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

                    _compileAndCheckShader(vertexShader, vertex);
                    _compileAndCheckShader(fragmentShader, fragment);

                    _program = _linkProgram(vertexShader, fragmentShader);

                    glDetachShader(_program, vertexShader);
                    glDetachShader(_program, fragmentShader);

                    glDeleteShader(vertexShader);
                    glDeleteShader(fragmentShader);

                    glUseProgram(_program);

                    _modelMatrixHandle = glGetUniformLocation(_program, "modelMatrix");
                    _projectionViewMatrixHandle = glGetUniformLocation(_program, "projectionViewMatrix");
                }

                void render() {
                    glUseProgram(_program);
                }

                void setModelMatrix(glm::mat4 const& matrix) {
                    glUniformMatrix4fv(_modelMatrixHandle, 1, GL_FALSE, &matrix[0][0]);
                }

                void setProjectionViewMatrix(glm::mat4 const& matrix) {
                    glUniformMatrix4fv(_projectionViewMatrixHandle, 1, GL_FALSE, &matrix[0][0]);
                }

            private:
                GLuint _program;
                GLuint _modelMatrixHandle;
                GLuint _projectionViewMatrixHandle;

                static bool _compileAndCheckShader(GLuint id, const char* shader) {
                    glShaderSource(id, 1, &shader, NULL);
                    glCompileShader(id);

                    GLint result = GL_FALSE;
                    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
                    
                    int infoLogLength = 0;
                    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

                    if(infoLogLength > 1) {
                        char* buffer = new char[infoLogLength+1];

                        glGetShaderInfoLog(id, infoLogLength, NULL, buffer);
                        std::cerr << "Shader compilation failed:" << std::endl
                                  << std::string(buffer, buffer + infoLogLength) << std::endl;
                        delete[] buffer;
                    }

                    return result == GL_TRUE;
                }

                static GLuint _linkProgram(GLuint vertexID, GLuint fragmentID) {
                    GLuint program = glCreateProgram();
                    glAttachShader(program, vertexID);
                    glAttachShader(program, fragmentID);
                    glLinkProgram(program);

                    GLint result = GL_FALSE;
                    glGetProgramiv(program, GL_LINK_STATUS, &result);

                    if(result != GL_TRUE) {
                        std::cerr << "Error linking shader program" << std::endl;
                    }

                    int infoLogLength = 0;
                    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

                    if(infoLogLength > 1) {
                        char* buffer = new char[infoLogLength+1];

                        glGetProgramInfoLog(program, infoLogLength, NULL, buffer);
                        std::cerr << "Shader linking failed:" << std::endl
                                  << buffer << std::endl;
                        delete[] buffer;
                    }

                    return program;
            }
        };
    }
}

#endif
