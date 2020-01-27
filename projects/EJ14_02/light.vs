#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
out vec3 normal;
out vec3 fragPos;
out vec2 uv;

void main() {
    uv = aUv;
    fragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}