#version 330 core

out vec4 FragColor;

in vec3 phong;
in vec3 fragPos;

void main() {
    FragColor = vec4(phong, 1.0f);
}