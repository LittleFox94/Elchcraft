#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 modelMatrix;
uniform mat4 projectionViewMatrix;

void main() {
    gl_Position = projectionViewMatrix * modelMatrix * vec4(vertexPosition_modelspace, 1);
}
