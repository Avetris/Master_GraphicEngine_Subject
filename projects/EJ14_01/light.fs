#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 uv;

uniform vec3 lightColor;

void main() {
    FragColor = vec4(lightColor, 1.0f);
}