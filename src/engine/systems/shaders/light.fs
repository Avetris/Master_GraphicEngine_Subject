#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 uv;

uniform vec3 modelColor;

void main() {
    FragColor = vec4(modelColor, 1.0f);
}