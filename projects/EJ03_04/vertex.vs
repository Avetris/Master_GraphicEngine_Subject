#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;

out vec3 myColor;
out vec3 vertexPosition;  // Pasamos como parametro la posicion del vertice

void main() {
    myColor = aColor;
	vertexPosition = aPos;
    gl_Position = vec4(aPos, 1.0);
}