#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;

out vec3 myColor;

void main() {
    myColor = aColor;
    gl_Position = vec4(aPos, 1.0);
    gl_Position.y = gl_Position.y * -1; // Damos la vuelta al vertice
    if(gl_Position.y == 0.5){
        gl_Position.x = gl_Position.x * -1; // Como el orden de los vertices ha cambiado, tenemos tambien que cambiar el orden de los vertices en el eje x.
    }
}