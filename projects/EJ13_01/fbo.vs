#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUv;
layout (location=2) in vec3 aNormal;

out vec2 uv;
uniform mat4 model;

void main() {
    uv = aUv;
    gl_Position = model * vec4(aPos, 1.0);
}