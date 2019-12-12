#version 330 core

in vec2 UV;
out vec4 FragColor;

uniform sampler2D tex_1;
uniform sampler2D tex_2;

void main() {
    FragColor = texture(tex_2, vec2(UV.x, UV.y * -1)); // Al asignar a la textura la posicion, introducimos la posicion inversa de Y (posicion de Y por -1)
	//FragColor = texture(tex_2, UV); // Para comprobar que sin aplicar esa inversion, la imagen esta al reves, se debe descomentar esta linea
}