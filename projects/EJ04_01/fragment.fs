#version 330 core

in vec2 UV;
in vec3 myColor;

out vec4 FragColor;

uniform sampler2D tex_1;

void main() {
    FragColor = mix(texture(tex_1, UV), vec4(myColor, 1.0f) , 0.7); // Hacemos el mix entre la textura y el color.
}