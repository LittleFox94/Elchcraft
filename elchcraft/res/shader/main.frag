#version 330 core

out vec3 color;

void main() {
    color = vec3(1, 0.2, gl_FragCoord.x / 1280);
}
